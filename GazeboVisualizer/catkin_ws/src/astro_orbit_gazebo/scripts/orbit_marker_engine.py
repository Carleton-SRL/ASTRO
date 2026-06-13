#!/usr/bin/env python3
import rospy
from nav_msgs.msg import Odometry
from visualization_msgs.msg import Marker, MarkerArray
from geometry_msgs.msg import Point

class OrbitMarkerEngine:
    def __init__(self):
        self.target_topic = rospy.get_param('~target_topic', '/astro/target/state')
        self.chaser_topic = rospy.get_param('~chaser_topic', '/astro/chaser/state')
        self.position_units = rospy.get_param('~position_units', 'km').lower()
        self.visual_scale = float(rospy.get_param('~visual_scale', 0.01))
        self.center_mode = rospy.get_param('~center_mode', 'target').lower()
        self.max_points = int(rospy.get_param('~max_points', 4000))
        self.target = None
        self.target_path = []
        self.chaser_path = []
        self.pub = rospy.Publisher('/astro/visualization/markers', MarkerArray, queue_size=1)
        rospy.Subscriber(self.target_topic, Odometry, self.target_cb, queue_size=1)
        rospy.Subscriber(self.chaser_topic, Odometry, self.chaser_cb, queue_size=1)
        rospy.loginfo('ASTRO orbit_marker_engine ready.')
        rospy.spin()

    def unit_scale(self): return 1000.0 if self.position_units.startswith('km') else 1.0
    def raw_xyz_m(self, msg):
        s = self.unit_scale(); p = msg.pose.pose.position
        return [p.x*s, p.y*s, p.z*s]
    def origin_m(self):
        return self.raw_xyz_m(self.target) if (self.center_mode == 'target' and self.target is not None) else [0,0,0]
    def to_point(self, msg):
        p = self.raw_xyz_m(msg); o = self.origin_m()
        pt = Point(); pt.x=(p[0]-o[0])*self.visual_scale; pt.y=(p[1]-o[1])*self.visual_scale; pt.z=(p[2]-o[2])*self.visual_scale
        return pt
    def target_cb(self, msg):
        self.target = msg
        self.target_path.append(self.to_point(msg)); self.target_path = self.target_path[-self.max_points:]
        self.publish()
    def chaser_cb(self, msg):
        self.chaser_path.append(self.to_point(msg)); self.chaser_path = self.chaser_path[-self.max_points:]
        self.publish()
    def line_marker(self, marker_id, name, pts, r,g,b):
        m=Marker(); m.header.frame_id='world'; m.header.stamp=rospy.Time.now(); m.ns=name; m.id=marker_id; m.type=Marker.LINE_STRIP; m.action=Marker.ADD
        m.scale.x=0.25; m.color.r=r; m.color.g=g; m.color.b=b; m.color.a=1.0; m.points=pts
        return m
    def axis_marker(self):
        ma=[]; L=20.0
        colors=[(1,0,0),(0,1,0),(0,0.4,1)]; axes=[(L,0,0),(0,L,0),(0,0,L)]
        for i,a in enumerate(axes):
            m=Marker(); m.header.frame_id='world'; m.header.stamp=rospy.Time.now(); m.ns='inertial_axes'; m.id=10+i; m.type=Marker.ARROW; m.action=Marker.ADD
            m.scale.x=0.4; m.scale.y=0.8; m.scale.z=0.8; m.color.r=colors[i][0]; m.color.g=colors[i][1]; m.color.b=colors[i][2]; m.color.a=1
            p0=Point(); p1=Point(); p1.x=a[0]; p1.y=a[1]; p1.z=a[2]; m.points=[p0,p1]; ma.append(m)
        return ma
    def publish(self):
        arr=MarkerArray(); arr.markers.append(self.line_marker(1,'target_orbit',self.target_path,0.1,0.6,1.0)); arr.markers.append(self.line_marker(2,'chaser_orbit',self.chaser_path,1.0,0.45,0.05)); arr.markers.extend(self.axis_marker()); self.pub.publish(arr)

if __name__ == '__main__':
    rospy.init_node('orbit_marker_engine')
    OrbitMarkerEngine()
