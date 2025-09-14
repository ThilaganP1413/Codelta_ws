import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/thilaks/ROS2/Codelta_ws/install/delta_gz_sim'
