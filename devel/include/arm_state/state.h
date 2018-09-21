// Generated by gencpp from file arm_state/state.msg
// DO NOT EDIT!


#ifndef ARM_STATE_MESSAGE_STATE_H
#define ARM_STATE_MESSAGE_STATE_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace arm_state
{
template <class ContainerAllocator>
struct state_
{
  typedef state_<ContainerAllocator> Type;

  state_()
    : id(0)
    , position(0)
    , angle(0)  {
    }
  state_(const ContainerAllocator& _alloc)
    : id(0)
    , position(0)
    , angle(0)  {
  (void)_alloc;
    }



   typedef uint8_t _id_type;
  _id_type id;

   typedef uint16_t _position_type;
  _position_type position;

   typedef uint16_t _angle_type;
  _angle_type angle;





  typedef boost::shared_ptr< ::arm_state::state_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::arm_state::state_<ContainerAllocator> const> ConstPtr;

}; // struct state_

typedef ::arm_state::state_<std::allocator<void> > state;

typedef boost::shared_ptr< ::arm_state::state > statePtr;
typedef boost::shared_ptr< ::arm_state::state const> stateConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::arm_state::state_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::arm_state::state_<ContainerAllocator> >::stream(s, "", v);
return s;
}

} // namespace arm_state

namespace ros
{
namespace message_traits
{



// BOOLTRAITS {'IsFixedSize': True, 'IsMessage': True, 'HasHeader': False}
// {'arm_state': ['/home/kou256/ROS/EnterZen/src/arm_state/msg'], 'std_msgs': ['/opt/ros/kinetic/share/std_msgs/cmake/../msg']}

// !!!!!!!!!!! ['__class__', '__delattr__', '__dict__', '__doc__', '__eq__', '__format__', '__getattribute__', '__hash__', '__init__', '__module__', '__ne__', '__new__', '__reduce__', '__reduce_ex__', '__repr__', '__setattr__', '__sizeof__', '__str__', '__subclasshook__', '__weakref__', '_parsed_fields', 'constants', 'fields', 'full_name', 'has_header', 'header_present', 'names', 'package', 'parsed_fields', 'short_name', 'text', 'types']




template <class ContainerAllocator>
struct IsFixedSize< ::arm_state::state_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::arm_state::state_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::arm_state::state_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::arm_state::state_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::arm_state::state_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::arm_state::state_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::arm_state::state_<ContainerAllocator> >
{
  static const char* value()
  {
    return "402d479cdb26ccff42ea9316f4bc75ef";
  }

  static const char* value(const ::arm_state::state_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x402d479cdb26ccffULL;
  static const uint64_t static_value2 = 0x42ea9316f4bc75efULL;
};

template<class ContainerAllocator>
struct DataType< ::arm_state::state_<ContainerAllocator> >
{
  static const char* value()
  {
    return "arm_state/state";
  }

  static const char* value(const ::arm_state::state_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::arm_state::state_<ContainerAllocator> >
{
  static const char* value()
  {
    return "uint8 id\n\
uint16 position\n\
uint16 angle\n\
";
  }

  static const char* value(const ::arm_state::state_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::arm_state::state_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.id);
      stream.next(m.position);
      stream.next(m.angle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct state_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::arm_state::state_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::arm_state::state_<ContainerAllocator>& v)
  {
    s << indent << "id: ";
    Printer<uint8_t>::stream(s, indent + "  ", v.id);
    s << indent << "position: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.position);
    s << indent << "angle: ";
    Printer<uint16_t>::stream(s, indent + "  ", v.angle);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ARM_STATE_MESSAGE_STATE_H
