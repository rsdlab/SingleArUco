// -*- C++ -*-
/*!
 * @file  SingleArUco.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "SingleArUco.h"

// Module specification
// <rtc-template block="module_spec">
static const char* singlearuco_spec[] =
  {
    "implementation_id", "SingleArUco",
    "type_name",         "SingleArUco",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "Yuki_Takamido",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.MarkerSize", "0.05",
    "conf.default.Dictionary", "ORIGINAL",

    // Widget
    "conf.__widget__.MarkerSize", "text",
    "conf.__widget__.Dictionary", "radio",
    // Constraints
    "conf.__constraints__.Dictionary", "(ORIGINAL,4x4_50,4x4_100,4x4_250,4x4_1000,5x5_50,5x5_100,5x5_250,5x5_1000,6x6_50,6x6_100,6x6_250,6x6_1000,7x7_50,7x7_100,7x7_250,7x7_1000)",

    "conf.__type__.MarkerSize", "double",
    "conf.__type__.Dictionary", "string",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
SingleArUco::SingleArUco(RTC::Manager* manager)
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
SingleArUco::~SingleArUco()
{
}



RTC::ReturnCode_t SingleArUco::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("InImage", m_InImageIn);
  
  // Set OutPort buffer
  addOutPort("OutImage", m_OutImageOut);
  addOutPort("arUcoPoint2D", m_arUcoPoint2DOut);
  addOutPort("arUcoPose3D", m_arUcoPose3DOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("MarkerSize", m_MarkerSize, "0.05");
  bindParameter("Dictionary", m_Dictionary, "ORIGINAL");
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SingleArUco::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUco::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUco::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t SingleArUco::onActivated(RTC::UniqueId ec_id)
{

  if(m_Dictionary=="ORIGINAL")
    {
      dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);
    }
  else if(m_Dictionary=="4x4_50")
    {
      dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
    }
  else if(m_Dictionary=="4x4_100")
    {
      dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_100);
    }
  else if(m_Dictionary=="4x4_250")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_250);
    }
  else if(m_Dictionary=="4x4_1000")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_1000);
    }
  else if(m_Dictionary=="5x5_50")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_50);
    }
  else if(m_Dictionary=="5x5_100")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_100);
    }
  else if(m_Dictionary=="5x5_250")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_250);
    }
  else if(m_Dictionary=="5x5_1000")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_5X5_1000);
    }
  else if(m_Dictionary=="6x6_50")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_50);
    }
  else if(m_Dictionary=="6x6_100")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_100);
    }
  else if(m_Dictionary=="6x6_250")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_250);
    }
  else if(m_Dictionary=="6x6_1000")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_6X6_1000);
    }
  else if(m_Dictionary=="7x7_50")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_50);
    }
  else if(m_Dictionary=="7x7_100")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_100);
    }
  else if(m_Dictionary=="7x7_250")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_250);
    }
  else if(m_Dictionary=="7x7_1000")
    {
dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_7X7_1000);
    }
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SingleArUco::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t SingleArUco::onExecute(RTC::UniqueId ec_id)
{
    //Inport data check
  //データポートが更新されているかの確認
  if(m_InImageIn.isNew())
    {
      m_InImageIn.read();//データポートを読み込む

      width=m_InImage.data.image.width;//データポートから画像幅を取得
      height=m_InImage.data.image.height;//データポートから画像の高さを取得
      channels=(m_InImage.data.image.format == Img::CF_GRAY) ? 1 :
			   (m_InImage.data.image.format == Img::CF_RGB || m_InImage.data.image.format == Img::CF_PNG || m_InImage.data.image.format == Img::CF_JPEG) ? 3 :
	(m_InImage.data.image.raw_data.length()/width/height);//チャンネル数の取得
      if(channels==3)//チャンネル数によるＭａｔのメモリ確保
	image.create(height,width,CV_8UC3);//8bit unsigned char型で３チャンネル(1pixelあたり３つ)
      else
	image.create(height,width,CV_8UC1);//8bit unsigned char型で1チャンネル(1pixelあたり1つ)

      long data_length=m_InImage.data.image.raw_data.length();//データポートから画像データの長さを取得

      if(m_InImage.data.image.format==Img::CF_RGB||m_InImage.data.image.format==Img::CF_GRAY)//データがRGB形式で送られてきている場合
	{
	  
	  for(int i=0;i<height;++i)//画像データを１行づつコピー
	    {
	      //memcpy(コピー先のポインタ,コピー元のポインタ,コピーするデータの長さ(バイト数))
	      //あるポインタから、指定のポインタに、指定された長さのメモリをコピーする
	      //sizeof(変数)
	      //引数で確保されているメモリをint型で返す
	      memcpy(&image.data[i*image.step],&m_InImage.data.image.raw_data[i*width*channels],sizeof(unsigned char)*width*channels);
	    }
	  
	  if(channels==3)//ＲＧＢの順番を変更(標準的に使われているカメラの出力の順番とOpenCVで用いられている順番が違うため)
	    {
	      cv::cvtColor(image,image,CV_RGB2BGR);//チャンネルの順番をＲＧＢからＢＧＲに変更
	    }
	  
	}
      else if(m_InImage.data.image.format==Img::CF_JPEG||m_InImage.data.image.format==Img::CF_PNG)//データがJPEC,PNG形式で送られてきた場合
	{
	  std::vector<uchar> compressed_image=std::vector<uchar>(data_length);//unsigned char型の配列をdata_length列文確保
	  //データコピー
	  memcpy(&compressed_image[0], &m_InImage.data.image.raw_data[0], sizeof(unsigned char) * data_length);

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


      std::vector<cv::Vec3d> rvecs,tvecs;
      

      //データポートからカメラパラメータを取得
      CameraParam.at<float>(0,0)=m_InImage.data.intrinsic.matrix_element[0];
      CameraParam.at<float>(0,2)=m_InImage.data.intrinsic.matrix_element[1];
      CameraParam.at<float>(1,1)=m_InImage.data.intrinsic.matrix_element[2];
      CameraParam.at<float>(1,2)=m_InImage.data.intrinsic.matrix_element[3];
      CameraParam.at<float>(2,2)=1;

      int distCoeffs_length=m_InImage.data.intrinsic.distortion_coefficient.length();
      distCoeffs=cv::Mat::zeros(1,distCoeffs_length,CV_32F);
	for(int i=0;i<distCoeffs_length;i++)
	  {
	    distCoeffs.at<float>(0,i)=(float)m_InImage.data.intrinsic.distortion_coefficient[i];
	  }

	//出力データポート用にカメラパラメータを格納
        m_OutImage.data.intrinsic.matrix_element[0]=m_InImage.data.intrinsic.matrix_element[0];
	m_OutImage.data.intrinsic.matrix_element[1]=m_InImage.data.intrinsic.matrix_element[1];
	m_OutImage.data.intrinsic.matrix_element[2]=m_InImage.data.intrinsic.matrix_element[2];
	m_OutImage.data.intrinsic.matrix_element[3]=m_InImage.data.intrinsic.matrix_element[3];
	m_OutImage.data.intrinsic.matrix_element[4]=1;

	m_OutImage.data.intrinsic.distortion_coefficient.length(distCoeffs_length);
	for(int i=0;i<distCoeffs_length;i++)
	  {
	    distCoeffs.at<float>(0,i)=(float)m_InImage.data.intrinsic.distortion_coefficient[i];
	    m_OutImage.data.intrinsic.distortion_coefficient[i]=m_InImage.data.intrinsic.distortion_coefficient[i];
	  }
	
	
	
      	cv::aruco::detectMarkers(image,dictionary,markerCorners,markerIds,parameters,rejectedCandidates/*,CameraParam,distCoeffs*/);//マーカの位置を特定
	//cv::aruco::detectMarkers(image,dictionary, markerCorners, markerIds,parameters,rejectedCandidates,CameraParam,distCoeffs);
	cv::aruco::drawDetectedMarkers(image,markerCorners,markerIds);//検出したマーカを表示す
	cv::aruco::estimatePoseSingleMarkers(markerCorners,m_MarkerSize,CameraParam,distCoeffs,rvecs,tvecs);//コーナからＲＴを求める

	//出力時の動的配列の長さを確保
	m_arUcoPoint2D.ids.length(markerIds.size());
	m_arUcoPoint2D.markerCorners.length(markerIds.size());
	m_arUcoPose3D.ids.length(markerIds.size());
	m_arUcoPose3D.rotations.length(markerIds.size());
	m_arUcoPose3D.translates.length(markerIds.size());
	
	if(markerIds.size()>0)
	  {
	    for(int i=0;i<markerIds.size();i++)
	      {
		cv::aruco::drawAxis(image,CameraParam,distCoeffs,rvecs[i],tvecs[i],0.1);//各軸を表示する
		//回転行列の変換
		cv::Mat RMat=cv::Mat::zeros(3,3,CV_32F);
		cv::Rodrigues(rvecs[i],RMat);
	     
		
		//マーカＩＤ格納
		m_arUcoPoint2D.ids[i]=markerIds[i];
		m_arUcoPose3D.ids[i]=markerIds[i];

		//コーナ格納
		m_arUcoPoint2D.markerCorners[i].point1.x=markerCorners[i][0].x;
		m_arUcoPoint2D.markerCorners[i].point1.y=markerCorners[i][0].y;
		m_arUcoPoint2D.markerCorners[i].point2.x=markerCorners[i][1].x;
		m_arUcoPoint2D.markerCorners[i].point2.y=markerCorners[i][1].y;
		m_arUcoPoint2D.markerCorners[i].point3.x=markerCorners[i][2].x;
		m_arUcoPoint2D.markerCorners[i].point3.y=markerCorners[i][2].y;
		m_arUcoPoint2D.markerCorners[i].point4.x=markerCorners[i][3].x;
		m_arUcoPoint2D.markerCorners[i].point4.y=markerCorners[i][3].y;

		//ＲＴの格納
		m_arUcoPose3D.rotations[i].R11=(double)RMat.at<float>(0,0);
		m_arUcoPose3D.rotations[i].R12=(double)RMat.at<float>(0,1);
		m_arUcoPose3D.rotations[i].R13=(double)RMat.at<float>(0,2);
		m_arUcoPose3D.rotations[i].R21=(double)RMat.at<float>(1,0);
		m_arUcoPose3D.rotations[i].R22=(double)RMat.at<float>(1,1);
		m_arUcoPose3D.rotations[i].R23=(double)RMat.at<float>(1,2);
		m_arUcoPose3D.rotations[i].R31=(double)RMat.at<float>(2,0);
		m_arUcoPose3D.rotations[i].R32=(double)RMat.at<float>(2,1);
		m_arUcoPose3D.rotations[i].R33=(double)RMat.at<float>(2,2);
		m_arUcoPose3D.translates[i].x=(double)tvecs[i][0];
		m_arUcoPose3D.translates[i].y=(double)tvecs[i][1];
		m_arUcoPose3D.translates[i].z=(double)tvecs[i][2];
		/*
		std::cout<<" RMat "<<std::endl<<RMat<<std::endl;
		std::cout<<" Trans : "<<m_arUcoPose3D.translates[i].x<<" , "<<m_arUcoPose3D.translates[i].y<<" , "<<m_arUcoPose3D.translates[i].z<<std::endl<<RMat<<std::endl;
		*/
		/*
		if(markerIds[i]==2)
		  {
		    std::cout<<" R = "<<RMat<<std::endl;
		    std::cout<<" T = "<<tvecs[i]<<std::endl;
		  }
		*/
	      }
	    
	    m_arUcoPoint2DOut.write();
	    m_arUcoPose3DOut.write();
	  }
	
      //画像データが入っている場合は画像を表示
	/**/
      if(!image.empty())
	{
	  cv::imshow("Image Window",image);
	  cv::waitKey(3);
	  //結果の画像出力
	  m_OutImage.data.image.width=width;//データポートに画像幅を出力
	  m_OutImage.data.image.height=height;//データポートに画像の高さを出力
	  
	  //データ長さの指定
	  m_OutImage.data.image.raw_data.length(width*height*channels);
	  
	  if(channels==3)//カラー画像の場合
	    {
	      //フォーマットの指定
	      m_OutImage.data.image.format=Img::CF_RGB;
	  
	      //RGBの変更
	      cv::cvtColor(image,image,CV_RGB2BGR);
	  
	    }
	  else
	    {
	      //フォーマットの指定
	      m_OutImage.data.image.format=Img::CF_GRAY;
	    }
	  for( int i(0); i< height; ++i )
	    {
	      memcpy(&m_OutImage.data.image.raw_data[ i * width * channels], &image.data[ i * image.step ], width * channels);
	    }
	}
      m_OutImageOut.write();

    }

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t SingleArUco::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUco::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUco::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUco::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t SingleArUco::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void SingleArUcoInit(RTC::Manager* manager)
  {
    coil::Properties profile(singlearuco_spec);
    manager->registerFactory(profile,
                             RTC::Create<SingleArUco>,
                             RTC::Delete<SingleArUco>);
  }
  
};


