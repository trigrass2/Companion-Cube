"""autogenerated by genmsg_py from Encoder.msg. Do not edit."""
import roslib.message
import struct

import std_msgs.msg

class Encoder(roslib.message.Message):
  _md5sum = "63b24db5a3c143c57912a66b55703ac8"
  _type = "rover_msgs/Encoder"
  _has_header = True #flag to mark the presence of a Header object
  _full_text = """Header header
float32 left
float32 right
int32 leftCount
int32 rightCount
int32 leftMotor
int32 rightMotor
float32 left_conversion_factor
float32 right_conversion_factor

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.secs: seconds (stamp_secs) since epoch
# * stamp.nsecs: nanoseconds since stamp_secs
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
# 0: no frame
# 1: global frame
string frame_id

"""
  __slots__ = ['header','left','right','leftCount','rightCount','leftMotor','rightMotor','left_conversion_factor','right_conversion_factor']
  _slot_types = ['Header','float32','float32','int32','int32','int32','int32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.
    
    The available fields are:
       header,left,right,leftCount,rightCount,leftMotor,rightMotor,left_conversion_factor,right_conversion_factor
    
    @param args: complete set of field values, in .msg order
    @param kwds: use keyword arguments corresponding to message field names
    to set specific fields. 
    """
    if args or kwds:
      super(Encoder, self).__init__(*args, **kwds)
      #message fields cannot be None, assign default values for those that are
      if self.header is None:
        self.header = std_msgs.msg._Header.Header()
      if self.left is None:
        self.left = 0.
      if self.right is None:
        self.right = 0.
      if self.leftCount is None:
        self.leftCount = 0
      if self.rightCount is None:
        self.rightCount = 0
      if self.leftMotor is None:
        self.leftMotor = 0
      if self.rightMotor is None:
        self.rightMotor = 0
      if self.left_conversion_factor is None:
        self.left_conversion_factor = 0.
      if self.right_conversion_factor is None:
        self.right_conversion_factor = 0.
    else:
      self.header = std_msgs.msg._Header.Header()
      self.left = 0.
      self.right = 0.
      self.leftCount = 0
      self.rightCount = 0
      self.leftMotor = 0
      self.rightMotor = 0
      self.left_conversion_factor = 0.
      self.right_conversion_factor = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    @param buff: buffer
    @type  buff: StringIO
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2f4i2f.pack(_x.left, _x.right, _x.leftCount, _x.rightCount, _x.leftMotor, _x.rightMotor, _x.left_conversion_factor, _x.right_conversion_factor))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    @param str: byte array of serialized message
    @type  str: str
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg._Header.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 32
      (_x.left, _x.right, _x.leftCount, _x.rightCount, _x.leftMotor, _x.rightMotor, _x.left_conversion_factor, _x.right_conversion_factor,) = _struct_2f4i2f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    @param buff: buffer
    @type  buff: StringIO
    @param numpy: numpy python module
    @type  numpy module
    """
    try:
      _x = self
      buff.write(_struct_3I.pack(_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs))
      _x = self.header.frame_id
      length = len(_x)
      buff.write(struct.pack('<I%ss'%length, length, _x))
      _x = self
      buff.write(_struct_2f4i2f.pack(_x.left, _x.right, _x.leftCount, _x.rightCount, _x.leftMotor, _x.rightMotor, _x.left_conversion_factor, _x.right_conversion_factor))
    except struct.error as se: self._check_types(se)
    except TypeError as te: self._check_types(te)

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    @param str: byte array of serialized message
    @type  str: str
    @param numpy: numpy python module
    @type  numpy: module
    """
    try:
      if self.header is None:
        self.header = std_msgs.msg._Header.Header()
      end = 0
      _x = self
      start = end
      end += 12
      (_x.header.seq, _x.header.stamp.secs, _x.header.stamp.nsecs,) = _struct_3I.unpack(str[start:end])
      start = end
      end += 4
      (length,) = _struct_I.unpack(str[start:end])
      start = end
      end += length
      self.header.frame_id = str[start:end]
      _x = self
      start = end
      end += 32
      (_x.left, _x.right, _x.leftCount, _x.rightCount, _x.leftMotor, _x.rightMotor, _x.left_conversion_factor, _x.right_conversion_factor,) = _struct_2f4i2f.unpack(str[start:end])
      return self
    except struct.error as e:
      raise roslib.message.DeserializationError(e) #most likely buffer underfill

_struct_I = roslib.message.struct_I
_struct_3I = struct.Struct("<3I")
_struct_2f4i2f = struct.Struct("<2f4i2f")
