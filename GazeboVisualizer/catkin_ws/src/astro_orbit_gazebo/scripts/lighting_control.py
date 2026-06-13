#!/usr/bin/env python3
import math
import rospy
from std_msgs.msg import String, ColorRGBA, Float64
from geometry_msgs.msg import Vector3
from nav_msgs.msg import Odometry
from gazebo_msgs.srv import SetLightProperties

class LightingControl:
    def __init__(self):
        self.light_name = rospy.get_param('~light_name', 'main_sun_light')
        self.mode_topic = rospy.get_param('~mode_topic', '/astro/viz/lighting_mode')
        self.sun_direction_topic = rospy.get_param('~sun_direction_topic', '/astro/viz/sun_direction')
        self.sun_state_topic = rospy.get_param('~sun_state_topic', '/astro/sun/state')
        self.intensity_topic = rospy.get_param('~intensity_topic', '/astro/viz/light_intensity')
        self.initial_mode = rospy.get_param('~initial_mode', 'day')
        self.current_direction = self.vec(-0.5, 0.2, -0.8)
        self.current_color = self.color(1.0, 1.0, 1.0)
        self.current_intensity = 1.0
        rospy.Subscriber(self.mode_topic, String, self.mode_cb, queue_size=1)
        rospy.Subscriber(self.sun_direction_topic, Vector3, self.direction_cb, queue_size=1)
        rospy.Subscriber(self.sun_state_topic, Odometry, self.sun_state_cb, queue_size=1)
        rospy.Subscriber(self.intensity_topic, Float64, self.intensity_cb, queue_size=1)
        rospy.loginfo('Waiting for /gazebo/set_light_properties...')
        rospy.wait_for_service('/gazebo/set_light_properties')
        self.set_light = rospy.ServiceProxy('/gazebo/set_light_properties', SetLightProperties)
        rospy.sleep(1.0)
        self.apply_mode(self.initial_mode)
        rospy.loginfo('ASTRO lighting_control ready. Modes: day, dawn, eclipse, moonlight, soft, bright')
        rospy.spin()
    def color(self, r, g, b, a=1.0):
        c = ColorRGBA(); c.r = r; c.g = g; c.b = b; c.a = a; return c
    def scaled_color(self):
        return self.color(self.current_color.r*self.current_intensity, self.current_color.g*self.current_intensity, self.current_color.b*self.current_intensity, 1.0)
    def vec(self, x, y, z):
        n = math.sqrt(x*x + y*y + z*z)
        v = Vector3()
        if n < 1e-12: v.x, v.y, v.z = -0.5, 0.2, -0.8
        else: v.x, v.y, v.z = x/n, y/n, z/n
        return v
    def call(self):
        try: self.set_light(self.light_name, self.scaled_color(), 1.0, 0.0, 0.0, self.current_direction)
        except Exception as e: rospy.logwarn_throttle(2.0, 'set_light_properties failed: %s', str(e))
    def apply_mode(self, mode):
        m = str(mode).strip().lower()
        if m in ['day', 'sunlit', 'default']:
            self.current_color = self.color(1.0, 1.0, 1.0); self.current_intensity = 1.0
        elif m in ['dawn', 'dusk', 'terminator']:
            self.current_color = self.color(1.0, 0.58, 0.25); self.current_intensity = 0.75
        elif m in ['eclipse', 'night', 'dark']:
            self.current_color = self.color(0.025, 0.03, 0.045); self.current_intensity = 0.35
        elif m in ['moon', 'moonlight']:
            self.current_color = self.color(0.18, 0.22, 0.35); self.current_intensity = 0.55
        elif m in ['soft', 'inspection']:
            self.current_color = self.color(0.65, 0.70, 0.85); self.current_intensity = 0.85
        elif m in ['bright', 'high', 'high_contrast']:
            self.current_color = self.color(1.0, 0.95, 0.85); self.current_intensity = 1.4
        else:
            rospy.logwarn('Unknown lighting mode "%s".', mode); return
        self.call(); rospy.loginfo('Lighting mode set to %s', m)
    def mode_cb(self, msg): self.apply_mode(msg.data)
    def direction_cb(self, msg):
        self.current_direction = self.vec(msg.x, msg.y, msg.z); self.call()
    def intensity_cb(self, msg):
        self.current_intensity = max(0.0, float(msg.data)); self.call()
    def sun_state_cb(self, msg):
        p = msg.pose.pose.position
        self.current_direction = self.vec(-p.x, -p.y, -p.z); self.call()
if __name__ == '__main__':
    rospy.init_node('lighting_control'); LightingControl()
