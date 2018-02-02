// -*- C++ -*-
/*!
 * @file  SingleArUcoTestComp.cpp
 * @brief Sample
 * @date $Date$
 *
 * $Id$
 */

#include "SingleArUcoTestComp.h"

// Module specification
// <rtc-template block="module_spec">
static const char* singlearucotestcomp_spec[] =
  {
    "implementation_id", "SingleArUcoTestComp",
    "type_name",         "SingleArUcoTestComp",
    "description",       "Sample",
    "version",           "1.0.0",
    "vendor",            "YukiTakamido",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SingleArUcoTestComp::SingleArUcoTestComp(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ImageIn("Image", m_Image),
    m_arUcoPoint2DIn("arUcoPoint2D", m_arUcoPoint2D),
    m_arUcoPose3DIn("arUcoPose3D", m_arUcoPose3D)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
SingleArUcoTestComp::~SingleArUcoTestComp()
{
}



RTC::ReturnCode_t SingleArUcoTestComp::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("Image", m_ImageIn);
  addInPort("arUcoPoint2D", m_arUcoPoint2DIn);
  addInPort("arUcoPose3D", m_arUcoPose3DIn);
  
  // Set OutPort buffer
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SingleArUcoTestComp::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTestComp::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTestComp::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SingleArUcoTestComp::onActivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SingleArUcoTestComp::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SingleArUcoTestComp::onExecute(RTC::UniqueId ec_id)
{
  //データポートの読み込み
   if(m_ImageIn.isNew())
    {
      while(!m_ImageIn.isEmpty())
	m_ImageIn.read();

      width=m_Image.data.image.width;//データポートから画像幅を取得
      height=m_Image.data.image.height;//データポートから画像の高さを取得
      channels=(m_Image.data.image.format == Img::CF_GRAY) ? 1 :
	(m_Image.data.image.format == Img::CF_RGB || m_Image.data.image.format == Img::CF_PNG || m_Image.data.image.format == Img::CF_JPEG) ? 3 :
	(m_Image.data.image.raw_data.length()/width/height);//チャンネル数の取得
      if(channels==3)//チャンネル数によるＭａｔのメモリ確保
	image.create(height,width,CV_8UC3);//8bit unsigned char型で３チャンネル(1pixelあたり３つ)
      else
	image.create(height,width,CV_8UC1);//8bit unsigned char型で1チャンネル(1pixelあたり1つ)

      long data_length=m_Image.data.image.raw_data.length();//データポートから画像データの長さを取得

      if(m_Image.data.image.format==Img::CF_RGB||m_Image.data.image.format==Img::CF_GRAY)//データがRGB形式で送られてきている場合
	{
	  
	  for(int i=0;i<height;++i)//画像データを１行づつコピー
	    {
	      //memcpy(コピー先のポインタ,コピー元のポインタ,コピーするデータの長さ(バイト数))
	      //あるポインタから、指定のポインタに、指定された長さのメモリをコピーする
	      //sizeof(変数)
	      //引数で確保されているメモリをint型で返す
	      memcpy(&image.data[i*image.step],&m_Image.data.image.raw_data[i*width*channels],sizeof(unsigned char)*width*channels);
	    }
	  
	  if(channels==3)//ＲＧＢの順番を変更(標準的に使われているカメラの出力の順番とOpenCVで用いられている順番が違うため)
	    {
	      cv::cvtColor(image,image,CV_RGB2BGR);//チャンネルの順番をＲＧＢからＢＧＲに変更
	    }
	  
	}
      else if(m_Image.data.image.format==Img::CF_JPEG||m_Image.data.image.format==Img::CF_PNG)//データがJPEC,PNG形式で送られてきた場合
	{
	  std::vector<uchar> compressed_image=std::vector<uchar>(data_length);//unsigned char型の配列をdata_length列文確保
	  //データコピー
	  memcpy(&compressed_image[0], &m_Image.data.image.raw_data[0], sizeof(unsigned char) * data_length);

	  //データのデコード
	  cv::Mat decode_image;
	  if(channels==3)//3チャンネルの場合
	    {
	      decode_image=cv::imdecode(cv::Mat(compressed_image),CV_LOAD_IMAGE_COLOR);
	      cv::cvtColor(decode_image,image,CV_RGB2BGR);
	    }
	  else
	    {
	      decode_image=cv::imdecode(cv::Mat(compressed_image),CV_LOAD_IMAGE_GRAYSCALE);
	      image=decode_image;
	    }
	}

      //画像が読み込めている場合表示する
      if(!image.empty())
	{
	  cv::imshow("Image",image);
	  cv::waitKey(1);
	}      
    }
   if(m_arUcoPose3DIn.isNew())
     {
       while(!m_arUcoPose3DIn.isEmpty())
	 m_arUcoPose3DIn.read();

       for(int i=0;i<m_arUcoPose3D.ids.length();i++)
	 {
	   std::cout<<"Id : "<<m_arUcoPose3D.ids[i]<<std::endl;
	   std::cout<<"Rotation : "<<std::endl
		    <<m_arUcoPose3D.rotations[i].R11<<" , "<<m_arUcoPose3D.rotations[i].R12<<" , "<<m_arUcoPose3D.rotations[i].R13<<std::endl
		    <<m_arUcoPose3D.rotations[i].R21<<" , "<<m_arUcoPose3D.rotations[i].R22<<" , "<<m_arUcoPose3D.rotations[i].R23<<std::endl
		    <<m_arUcoPose3D.rotations[i].R31<<" , "<<m_arUcoPose3D.rotations[i].R32<<" , "<<m_arUcoPose3D.rotations[i].R33<<std::endl
		    <<std::endl;
	   std::cout<<"Translate : [ "<<m_arUcoPose3D.translates[i].x<<" , "<<m_arUcoPose3D.translates[i].y<<" , "<<m_arUcoPose3D.translates[i].z<<" ]"<<std::endl;
	 }
     }
      if(m_arUcoPoint2DIn.isNew())
     {
       while(!m_arUcoPoint2DIn.isEmpty())
	 m_arUcoPoint2DIn.read();
       for(int i=0;i<m_arUcoPoint2D.ids.length();i++)
	 {
	   std::cout<<"Id : "<<m_arUcoPoint2D.ids[i]<<std::endl;
	   std::cout<<"markerCornerTranslate : "<<std::endl
		    <<" Point1 : "<<m_arUcoPoint2D.markerCorners[i].point1.x<<" , "<<m_arUcoPoint2D.markerCorners[i].point1.y<<std::endl
		    <<" Point2 : "<<m_arUcoPoint2D.markerCorners[i].point2.x<<" , "<<m_arUcoPoint2D.markerCorners[i].point2.y<<std::endl
		    <<" Point3 : "<<m_arUcoPoint2D.markerCorners[i].point3.x<<" , "<<m_arUcoPoint2D.markerCorners[i].point3.y<<std::endl
		    <<" Point4 : "<<m_arUcoPoint2D.markerCorners[i].point4.x<<" , "<<m_arUcoPoint2D.markerCorners[i].point4.y<<std::endl;
	 }
       
     }
      
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SingleArUcoTestComp::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTestComp::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTestComp::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTestComp::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUcoTestComp::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SingleArUcoTestCompInit(RTC::Manager* manager)
  {
    coil::Properties profile(singlearucotestcomp_spec);
    manager->registerFactory(profile,
                             RTC::Create<SingleArUcoTestComp>,
                             RTC::Delete<SingleArUcoTestComp>);
  }
  
};


