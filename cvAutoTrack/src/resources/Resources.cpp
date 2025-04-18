#include "pch.h"
#include "Resources.h"
#include "resource.h"
#include <wincodec.h>
namespace TianLi::Resource::Utils
{
	void LoadBitmap_ID2Mat(int IDB, cv::Mat& mat)
	{
		auto H_Handle = LoadBitmap(GetModuleHandleW(L"CVAUTOTRACK.dll"), MAKEINTRESOURCE(IDB));
		BITMAP bmp;
		GetObject(H_Handle, sizeof(BITMAP), &bmp);
		int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
		//int depth = bmp.bmBitsPixel == 1 ? 1 : 8;
		cv::Mat v_mat;
		v_mat.create(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8UC3, nChannels));
		GetBitmapBits(H_Handle, bmp.bmHeight * bmp.bmWidth * nChannels, v_mat.data);
		mat = v_mat;
	}
	bool HBitmap2MatAlpha(HBITMAP& _hBmp, cv::Mat& _mat)
	{
		//BITMAP操作
		BITMAP bmp;
		GetObject(_hBmp, sizeof(BITMAP), &bmp);
		int nChannels = bmp.bmBitsPixel == 1 ? 1 : bmp.bmBitsPixel / 8;
		//int depth = bmp.bmBitsPixel == 1 ? 1 : 8;
		//mat操作
		cv::Mat v_mat;
		v_mat.create(cv::Size(bmp.bmWidth, bmp.bmHeight), CV_MAKETYPE(CV_8UC3, nChannels));
		GetBitmapBits(_hBmp, bmp.bmHeight * bmp.bmWidth * nChannels, v_mat.data);
		_mat = v_mat;
		return true;
	}
	void LoadPng_ID2Mat(int IDB, cv::Mat& mat)
	{
		IWICStream* pIWICStream = NULL;
		IWICBitmapDecoder* pIDecoder = NULL;
		IWICBitmapFrameDecode* pIDecoderFrame = NULL;
		IWICBitmapSource* bitmap_source = NULL;
		HRSRC imageResHandle = NULL;
		HGLOBAL imageResDataHandle = NULL;
		void* pImageFile = NULL;
		DWORD imageFileSize = 0;
		IWICImagingFactory* m_pIWICFactory = NULL;

		HMODULE hModu = GetModuleHandleW(L"CVAUTOTRACK.dll");

		if (hModu == NULL) throw "Get Dll Instance Fail!";


		CoInitializeEx(NULL, COINIT_MULTITHREADED);

		CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_PPV_ARGS(&m_pIWICFactory)
		);
		imageResHandle = FindResource(hModu, MAKEINTRESOURCE(IDB), L"PNG");
		imageResDataHandle = LoadResource(hModu, imageResHandle);
		pImageFile = LockResource(imageResDataHandle);
		imageFileSize = SizeofResource(hModu, imageResHandle);
		m_pIWICFactory->CreateStream(&pIWICStream);

		pIWICStream->InitializeFromMemory(
			reinterpret_cast<BYTE*>(pImageFile),
			imageFileSize);
		m_pIWICFactory->CreateDecoderFromStream(
			pIWICStream,                   // The stream to use to create the decoder
			NULL,                          // Do not prefer a particular vendor
			WICDecodeMetadataCacheOnLoad,  // Cache metadata when needed
			&pIDecoder);                   // Pointer to the decoder
		pIDecoder->GetFrame(0, &pIDecoderFrame);

		bitmap_source = pIDecoderFrame;

		UINT width = 0, height = 0, depht = 4;
		bitmap_source->GetSize(&width, &height);
		{
			std::vector<BYTE> buffer(width * height * depht);
			bitmap_source->CopyPixels(NULL, width * depht, static_cast<UINT>(buffer.size()), buffer.data());
			HBITMAP hPngMat = CreateBitmap(width, height, 1, 8 * depht, buffer.data());
			HBitmap2MatAlpha(hPngMat, mat);
			DeleteObject(hPngMat);
		}
		DeleteObject(bitmap_source);
		CoFreeUnusedLibraries();
		CoUninitialize();
	}
}
using namespace TianLi::Resource::Utils;
#ifdef USED_BINARY_IMAGE
#include "resources.load.h"
#endif // 
Resources::Resources()
{
#ifdef USED_BINARY_IMAGE
	PaimonTemplate = TianLi::Resources::Load::load_image("paimon");
	StarTemplate = TianLi::Resources::Load::load_image("star");
	MinimapCailbTemplate = TianLi::Resources::Load::load_image("cailb");
	UID = TianLi::Resources::Load::load_image("uid_");
	UIDnumber[0] = TianLi::Resources::Load::load_image("uid0");
	UIDnumber[1] = TianLi::Resources::Load::load_image("uid1");
	UIDnumber[2] = TianLi::Resources::Load::load_image("uid2");
	UIDnumber[3] = TianLi::Resources::Load::load_image("uid3");
	UIDnumber[4] = TianLi::Resources::Load::load_image("uid4");
	UIDnumber[5] = TianLi::Resources::Load::load_image("uid5");
	UIDnumber[6] = TianLi::Resources::Load::load_image("uid6");
	UIDnumber[7] = TianLi::Resources::Load::load_image("uid7");
	UIDnumber[8] = TianLi::Resources::Load::load_image("uid8");
	UIDnumber[9] = TianLi::Resources::Load::load_image("uid9");

	cv::cvtColor(StarTemplate, StarTemplate, cv::COLOR_RGB2GRAY);
	cv::cvtColor(UID, UID, cv::COLOR_RGB2GRAY);
	for (int i = 0; i < 10; i++)
	{
		cv::cvtColor(UIDnumber[i], UIDnumber[i], cv::COLOR_RGB2GRAY);
	}
#endif // 
	LoadBitmap_ID2Mat(IDB_BITMAP_PAIMON, PaimonTemplate);
	LoadBitmap_ID2Mat(IDB_BITMAP_STAR, StarTemplate);

	LoadPng_ID2Mat(IDB_PNG_MINIMAP_CAILB, MinimapCailbTemplate);

	LoadBitmap_ID2Mat(IDB_BITMAP_UID_, UID);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID0, UIDnumber[0]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID1, UIDnumber[1]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID2, UIDnumber[2]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID3, UIDnumber[3]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID4, UIDnumber[4]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID5, UIDnumber[5]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID6, UIDnumber[6]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID7, UIDnumber[7]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID8, UIDnumber[8]);
	LoadBitmap_ID2Mat(IDB_BITMAP_UID9, UIDnumber[9]);

	cv::cvtColor(StarTemplate, StarTemplate, cv::COLOR_RGBA2GRAY);
	cv::cvtColor(UID, UID, cv::COLOR_RGBA2GRAY);
	for (int i = 0; i < 10; i++)
	{
		cv::cvtColor(UIDnumber[i], UIDnumber[i], cv::COLOR_RGBA2GRAY);
	}
	
	// install();
}

Resources::~Resources()
{
	PaimonTemplate.release();
	MinimapCailbTemplate.release();
	StarTemplate.release();
	
	UID.release();
	UIDnumber[0].release();
	UIDnumber[1].release();
	UIDnumber[2].release();
	UIDnumber[3].release();
	UIDnumber[4].release();
	UIDnumber[5].release();
	UIDnumber[6].release();
	UIDnumber[7].release();
	UIDnumber[8].release();
	UIDnumber[9].release();
	release();
}

Resources& Resources::getInstance()
{
	static Resources instance;
	return instance;
}

void Resources::install()
{
	if (is_installed == false)
	{
		//LoadXml(xmlPtr);
		LoadPng_ID2Mat(IDB_PNG_GIMAP, MapTemplate);
		is_installed = true;
	}
}

void Resources::release()
{
	if (is_installed == true)
	{
		MapTemplate.release();
		MapTemplate = cv::Mat();
		//ReleaseXml(xmlPtr);
		is_installed = false;
	}
}

void Resources::get_map_keypoint_cache()
{

}