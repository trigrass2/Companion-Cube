/* Auto-generated by genmsg_cpp for file /home/rbtying/robot/rover_msgs/msg/Encoder.msg */
#ifndef ROVER_MSGS_MESSAGE_ENCODER_H
#define ROVER_MSGS_MESSAGE_ENCODER_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"

#include "std_msgs/Header.h"

namespace rover_msgs
{
template <class ContainerAllocator>
struct Encoder_ {
  typedef Encoder_<ContainerAllocator> Type;

  Encoder_()
  : header()
  , left(0.0)
  , right(0.0)
  , leftCount(0)
  , rightCount(0)
  , leftMotor(0)
  , rightMotor(0)
  , left_conversion_factor(0.0)
  , right_conversion_factor(0.0)
  {
  }

  Encoder_(const ContainerAllocator& _alloc)
  : header(_alloc)
  , left(0.0)
  , right(0.0)
  , leftCount(0)
  , rightCount(0)
  , leftMotor(0)
  , rightMotor(0)
  , left_conversion_factor(0.0)
  , right_conversion_factor(0.0)
  {
  }

  typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
   ::std_msgs::Header_<ContainerAllocator>  header;

  typedef float _left_type;
  float left;

  typedef float _right_type;
  float right;

  typedef int32_t _leftCount_type;
  int32_t leftCount;

  typedef int32_t _rightCount_type;
  int32_t rightCount;

  typedef int32_t _leftMotor_type;
  int32_t leftMotor;

  typedef int32_t _rightMotor_type;
  int32_t rightMotor;

  typedef float _left_conversion_factor_type;
  float left_conversion_factor;

  typedef float _right_conversion_factor_type;
  float right_conversion_factor;


private:
  static const char* __s_getDataType_() { return "rover_msgs/Encoder"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "63b24db5a3c143c57912a66b55703ac8"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "Header header\n\
float32 left\n\
float32 right\n\
int32 leftCount\n\
int32 rightCount\n\
int32 leftMotor\n\
int32 rightMotor\n\
float32 left_conversion_factor\n\
float32 right_conversion_factor\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, header);
    ros::serialization::serialize(stream, left);
    ros::serialization::serialize(stream, right);
    ros::serialization::serialize(stream, leftCount);
    ros::serialization::serialize(stream, rightCount);
    ros::serialization::serialize(stream, leftMotor);
    ros::serialization::serialize(stream, rightMotor);
    ros::serialization::serialize(stream, left_conversion_factor);
    ros::serialization::serialize(stream, right_conversion_factor);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, header);
    ros::serialization::deserialize(stream, left);
    ros::serialization::deserialize(stream, right);
    ros::serialization::deserialize(stream, leftCount);
    ros::serialization::deserialize(stream, rightCount);
    ros::serialization::deserialize(stream, leftMotor);
    ros::serialization::deserialize(stream, rightMotor);
    ros::serialization::deserialize(stream, left_conversion_factor);
    ros::serialization::deserialize(stream, right_conversion_factor);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(header);
    size += ros::serialization::serializationLength(left);
    size += ros::serialization::serializationLength(right);
    size += ros::serialization::serializationLength(leftCount);
    size += ros::serialization::serializationLength(rightCount);
    size += ros::serialization::serializationLength(leftMotor);
    size += ros::serialization::serializationLength(rightMotor);
    size += ros::serialization::serializationLength(left_conversion_factor);
    size += ros::serialization::serializationLength(right_conversion_factor);
    return size;
  }

  typedef boost::shared_ptr< ::rover_msgs::Encoder_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::rover_msgs::Encoder_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Encoder
typedef  ::rover_msgs::Encoder_<std::allocator<void> > Encoder;

typedef boost::shared_ptr< ::rover_msgs::Encoder> EncoderPtr;
typedef boost::shared_ptr< ::rover_msgs::Encoder const> EncoderConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::rover_msgs::Encoder_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::rover_msgs::Encoder_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace rover_msgs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::rover_msgs::Encoder_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::rover_msgs::Encoder_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::rover_msgs::Encoder_<ContainerAllocator> > {
  static const char* value() 
  {
    return "63b24db5a3c143c57912a66b55703ac8";
  }

  static const char* value(const  ::rover_msgs::Encoder_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x63b24db5a3c143c5ULL;
  static const uint64_t static_value2 = 0x7912a66b55703ac8ULL;
};

template<class ContainerAllocator>
struct DataType< ::rover_msgs::Encoder_<ContainerAllocator> > {
  static const char* value() 
  {
    return "rover_msgs/Encoder";
  }

  static const char* value(const  ::rover_msgs::Encoder_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::rover_msgs::Encoder_<ContainerAllocator> > {
  static const char* value() 
  {
    return "Header header\n\
float32 left\n\
float32 right\n\
int32 leftCount\n\
int32 rightCount\n\
int32 leftMotor\n\
int32 rightMotor\n\
float32 left_conversion_factor\n\
float32 right_conversion_factor\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.secs: seconds (stamp_secs) since epoch\n\
# * stamp.nsecs: nanoseconds since stamp_secs\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
";
  }

  static const char* value(const  ::rover_msgs::Encoder_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct HasHeader< ::rover_msgs::Encoder_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct HasHeader< const ::rover_msgs::Encoder_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::rover_msgs::Encoder_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.header);
    stream.next(m.left);
    stream.next(m.right);
    stream.next(m.leftCount);
    stream.next(m.rightCount);
    stream.next(m.leftMotor);
    stream.next(m.rightMotor);
    stream.next(m.left_conversion_factor);
    stream.next(m.right_conversion_factor);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Encoder_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::rover_msgs::Encoder_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::rover_msgs::Encoder_<ContainerAllocator> & v) 
  {
    s << indent << "header: ";
s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "left: ";
    Printer<float>::stream(s, indent + "  ", v.left);
    s << indent << "right: ";
    Printer<float>::stream(s, indent + "  ", v.right);
    s << indent << "leftCount: ";
    Printer<int32_t>::stream(s, indent + "  ", v.leftCount);
    s << indent << "rightCount: ";
    Printer<int32_t>::stream(s, indent + "  ", v.rightCount);
    s << indent << "leftMotor: ";
    Printer<int32_t>::stream(s, indent + "  ", v.leftMotor);
    s << indent << "rightMotor: ";
    Printer<int32_t>::stream(s, indent + "  ", v.rightMotor);
    s << indent << "left_conversion_factor: ";
    Printer<float>::stream(s, indent + "  ", v.left_conversion_factor);
    s << indent << "right_conversion_factor: ";
    Printer<float>::stream(s, indent + "  ", v.right_conversion_factor);
  }
};


} // namespace message_operations
} // namespace ros

#endif // ROVER_MSGS_MESSAGE_ENCODER_H

