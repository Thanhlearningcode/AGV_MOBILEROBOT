// Auto-generated. Do not edit!

// (in-package message_pkg.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class Vel_msg {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.pwm_left_motor = null;
      this.pwm_right_motor = null;
      this.vel_left_motor = null;
      this.vel_right_motor = null;
      this.dir = null;
    }
    else {
      if (initObj.hasOwnProperty('pwm_left_motor')) {
        this.pwm_left_motor = initObj.pwm_left_motor
      }
      else {
        this.pwm_left_motor = new std_msgs.msg.Int16();
      }
      if (initObj.hasOwnProperty('pwm_right_motor')) {
        this.pwm_right_motor = initObj.pwm_right_motor
      }
      else {
        this.pwm_right_motor = new std_msgs.msg.Int16();
      }
      if (initObj.hasOwnProperty('vel_left_motor')) {
        this.vel_left_motor = initObj.vel_left_motor
      }
      else {
        this.vel_left_motor = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('vel_right_motor')) {
        this.vel_right_motor = initObj.vel_right_motor
      }
      else {
        this.vel_right_motor = new std_msgs.msg.Float32();
      }
      if (initObj.hasOwnProperty('dir')) {
        this.dir = initObj.dir
      }
      else {
        this.dir = new std_msgs.msg.Int8();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Vel_msg
    // Serialize message field [pwm_left_motor]
    bufferOffset = std_msgs.msg.Int16.serialize(obj.pwm_left_motor, buffer, bufferOffset);
    // Serialize message field [pwm_right_motor]
    bufferOffset = std_msgs.msg.Int16.serialize(obj.pwm_right_motor, buffer, bufferOffset);
    // Serialize message field [vel_left_motor]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.vel_left_motor, buffer, bufferOffset);
    // Serialize message field [vel_right_motor]
    bufferOffset = std_msgs.msg.Float32.serialize(obj.vel_right_motor, buffer, bufferOffset);
    // Serialize message field [dir]
    bufferOffset = std_msgs.msg.Int8.serialize(obj.dir, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Vel_msg
    let len;
    let data = new Vel_msg(null);
    // Deserialize message field [pwm_left_motor]
    data.pwm_left_motor = std_msgs.msg.Int16.deserialize(buffer, bufferOffset);
    // Deserialize message field [pwm_right_motor]
    data.pwm_right_motor = std_msgs.msg.Int16.deserialize(buffer, bufferOffset);
    // Deserialize message field [vel_left_motor]
    data.vel_left_motor = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [vel_right_motor]
    data.vel_right_motor = std_msgs.msg.Float32.deserialize(buffer, bufferOffset);
    // Deserialize message field [dir]
    data.dir = std_msgs.msg.Int8.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 13;
  }

  static datatype() {
    // Returns string type for a message object
    return 'message_pkg/Vel_msg';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '8ce996bea8b23d23b9968c0c69988650';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    std_msgs/Int16 pwm_left_motor
    std_msgs/Int16 pwm_right_motor
    std_msgs/Float32 vel_left_motor
    std_msgs/Float32 vel_right_motor
    std_msgs/Int8 dir
    ================================================================================
    MSG: std_msgs/Int16
    int16 data
    
    ================================================================================
    MSG: std_msgs/Float32
    float32 data
    ================================================================================
    MSG: std_msgs/Int8
    int8 data
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Vel_msg(null);
    if (msg.pwm_left_motor !== undefined) {
      resolved.pwm_left_motor = std_msgs.msg.Int16.Resolve(msg.pwm_left_motor)
    }
    else {
      resolved.pwm_left_motor = new std_msgs.msg.Int16()
    }

    if (msg.pwm_right_motor !== undefined) {
      resolved.pwm_right_motor = std_msgs.msg.Int16.Resolve(msg.pwm_right_motor)
    }
    else {
      resolved.pwm_right_motor = new std_msgs.msg.Int16()
    }

    if (msg.vel_left_motor !== undefined) {
      resolved.vel_left_motor = std_msgs.msg.Float32.Resolve(msg.vel_left_motor)
    }
    else {
      resolved.vel_left_motor = new std_msgs.msg.Float32()
    }

    if (msg.vel_right_motor !== undefined) {
      resolved.vel_right_motor = std_msgs.msg.Float32.Resolve(msg.vel_right_motor)
    }
    else {
      resolved.vel_right_motor = new std_msgs.msg.Float32()
    }

    if (msg.dir !== undefined) {
      resolved.dir = std_msgs.msg.Int8.Resolve(msg.dir)
    }
    else {
      resolved.dir = new std_msgs.msg.Int8()
    }

    return resolved;
    }
};

module.exports = Vel_msg;
