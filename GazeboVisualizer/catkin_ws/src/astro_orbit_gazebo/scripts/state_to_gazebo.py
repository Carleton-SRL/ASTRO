#!/usr/bin/env python3
import rospy
from nav_msgs.msg import Odometry
from gazebo_msgs.srv import SetModelState
from gazebo_msgs.msg import ModelState
import tf

class StateToGazebo:
    def __init__(self):
        self.target_topic = rospy.get_param('~target_topic', '/astro/target/state')
        self.chaser_topic = rospy.get_param('~chaser_topic', '/astro/chaser/state')
        self.sun_topic = rospy.get_param('~sun_topic', '/astro/sun/state')
        self.moon_topic = rospy.get_param('~moon_topic', '/astro/moon/state')
        self.target_model = rospy.get_param('~target_model', 'target')
        self.chaser_model = rospy.get_param('~chaser_model', 'chaser')
        self.sun_model = rospy.get_param('~sun_model', 'sun_visual')
        self.moon_model = rospy.get_param('~moon_model', 'moon')
        self.position_units = rospy.get_param('~position_units', 'km').lower()
        self.visual_scale = float(rospy.get_param('~visual_scale', 0.01))
        self.celestial_visual_scale = float(rospy.get_param('~celestial_visual_scale', 1e-6))
        self.center_mode = rospy.get_param('~center_mode', 'target').lower()
        self.update_rate = float(rospy.get_param('~update_rate', 30.0))
        self.publish_tf = bool(rospy.get_param('~publish_tf', True))

        self.target = None
        self.chaser = None
        self.sun = None
        self.moon = None
        self.tfbr = tf.TransformBroadcaster()

        rospy.Subscriber(self.target_topic, Odometry, self.target_cb, queue_size=1)
        rospy.Subscriber(self.chaser_topic, Odometry, self.chaser_cb, queue_size=1)
        rospy.Subscriber(self.sun_topic, Odometry, self.sun_cb, queue_size=1)
        rospy.Subscriber(self.moon_topic, Odometry, self.moon_cb, queue_size=1)

        rospy.loginfo('Waiting for /gazebo/set_model_state...')
        rospy.wait_for_service('/gazebo/set_model_state')
        self.set_state = rospy.ServiceProxy('/gazebo/set_model_state', SetModelState)
        rospy.loginfo('ASTRO state_to_gazebo ready.')
        rospy.loginfo('  spacecraft: %s, %s', self.target_topic, self.chaser_topic)
        rospy.loginfo('  celestial:  %s, %s', self.sun_topic, self.moon_topic)
        self.loop()

    def target_cb(self, msg): self.target = msg
    def chaser_cb(self, msg): self.chaser = msg
    def sun_cb(self, msg): self.sun = msg
    def moon_cb(self, msg): self.moon = msg

    def unit_scale(self):
        if self.position_units in ['km', 'kilometer', 'kilometers']:
            return 1000.0
        return 1.0

    def raw_xyz_m(self, msg):
        s = self.unit_scale()
        p = msg.pose.pose.position
        return [p.x*s, p.y*s, p.z*s]

    def origin_m(self):
        if self.center_mode == 'target' and self.target is not None:
            return self.raw_xyz_m(self.target)
        if self.center_mode == 'chaser' and self.chaser is not None:
            return self.raw_xyz_m(self.chaser)
        return [0.0, 0.0, 0.0]

    def to_visual_xyz(self, msg, celestial=False):
        p = self.raw_xyz_m(msg)
        o = self.origin_m()
        scale = self.celestial_visual_scale if celestial else self.visual_scale
        return [(p[0]-o[0])*scale, (p[1]-o[1])*scale, (p[2]-o[2])*scale]

    def send_model(self, model_name, msg, celestial=False):
        xyz = self.to_visual_xyz(msg, celestial)
        q = msg.pose.pose.orientation
        st = ModelState()
        st.model_name = model_name
        st.reference_frame = 'world'
        st.pose.position.x, st.pose.position.y, st.pose.position.z = xyz
        st.pose.orientation = q
        try:
            self.set_state(st)
        except rospy.ServiceException as e:
            rospy.logwarn_throttle(2.0, 'set_model_state failed for %s: %s', model_name, str(e))
        if self.publish_tf:
            self.tfbr.sendTransform(tuple(xyz), (q.x, q.y, q.z, q.w), rospy.Time.now(), model_name, 'world')

    def loop(self):
        rate = rospy.Rate(self.update_rate)
        while not rospy.is_shutdown():
            if self.target is not None:
                self.send_model(self.target_model, self.target, celestial=False)
            if self.chaser is not None:
                self.send_model(self.chaser_model, self.chaser, celestial=False)
            if self.sun is not None:
                self.send_model(self.sun_model, self.sun, celestial=True)
            if self.moon is not None:
                self.send_model(self.moon_model, self.moon, celestial=True)
            rate.sleep()

if __name__ == '__main__':
    rospy.init_node('state_to_gazebo')
    StateToGazebo()
