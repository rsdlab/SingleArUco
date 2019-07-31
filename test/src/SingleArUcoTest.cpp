// -*- C++ -*-
/*!
 * @file  SingleArUcoTest.cpp
 * @brief Single ArUco RT Component
 * @date $Date$
 *
 * $Id$
 */

#include "SingleArUcoTest.h"

// Module specification
// <rtc-template block="module_spec">
static const char* singlearuco_spec[] =
  {
    "implementation_id", "SingleArUcoTest",
    "type_name",         "SingleArUcoTest",
    "description",       "Single ArUco RT Component",
    "version",           "1.1.0",
    "vendor",            "Robot System Design Laboratory, Meijo University",
    "category",          "ImageProcessing",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Dictionary", "ORIGINAL",
    "conf.default.MarkerSize", "0.05",

    // Widget
    "conf.__widget__.Dictionary", "text",
    "conf.__widget__.MarkerSize", "text",
    // Constraints

    "conf.__type__.Dictionary", "string",
    "conf.__type__.MarkerSize", "double",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SingleArUcoTest::SingleArUcoTest(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_InImageIn("InImage", m_InImage),
    m_OutImageOut("OutImage", m_OutImage),
    m_arUcoPoint2DOut("arUcoPoint2D", m_arUcoPoint2D),
    m_arUcoPose3DOut("arUcoPose3D", m_arUcoPose3D)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SingleArUcoTest::~SingleArUcoTest()
{
}



RTC::ReturnCode_t SingleArUcoTest::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("OutImage", m_OutImageIn);
  addInPort("arUcoPoint2D", m_arUcoPoint2DIn);
  addInPort("arUcoPose3D", m_arUcoPose3DIn);
  
  // Set OutPort buffer
  addOutPort("InImage", m_InImageOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Dictionary", m_Dictionary, "ORIGINAL");
  bindParameter("MarkerSize", m_MarkerSize, "0.05");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SingleArUcoTest::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTest::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTest::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SingleArUcoTest::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SingleArUcoTest::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SingleArUcoTest::onExecute(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SingleArUcoTest::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTest::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTest::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTest::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTest::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SingleArUcoTestInit(RTC::Manager* manager)
  {
    coil::Properties profile(singlearuco_spec);
    manager->registerFactory(profile,
                             RTC::Create<SingleArUcoTest>,
                             RTC::Delete<SingleArUcoTest>);
  }
  
};


