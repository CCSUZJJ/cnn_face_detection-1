#ifndef _NS_IMAGE_H_
#define _NS_IMAGE_H_

#include "ns_image_type.h"

//////////////////////////////////////////////////////////////////////////
#ifdef _WINDOWS
	#ifdef NS_IMAGE_EXPORTS
		#define NS_IMAGE_API __declspec(dllexport)
	#else
		#define NS_IMAGE_API __declspec(dllimport)
	#endif
#else	//_WINDOWS
	#define NS_IMAGE_API
#endif	//_WINDOWS

//////////////////////////////////////////////////////////////////////////

typedef enum NS_ImageEncodeType
{
	NS_IET_NONE = 0,
	NS_IET_JPG,
	NS_IET_BMP,
	NS_IET_TIF,
	NS_IET_PGM,
	NS_IET_PNG,
	NS_IET_J2K,
	NS_IET_JP2,
} NS_ImageEncodeType;

typedef struct NS_IMAGE
{
	unsigned char *pEnc;			// ����������ݵĻ�����
	unsigned char *pRaw;			// ����ԭʼͼ�����ݵĻ�������8λ���ҶȻ���BGR��ɫ

	NS_ImageEncodeType nEncType;	// �������ݵĸ�ʽ
	int nEncLen;					// ���뻺��������

	int nWidth, nHeight, nClrBit;	// ͼ��Ŀ��߼�ÿ������ռ�õ�bit��
	int nFlag;						// �ڲ�ʹ��

} NS_IMAGE;

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C"
{
#endif

	NS_IMAGE_API NS_RESULT NS_Image_Init(NS_IMAGE *pImage);
	/*
	������
		��ʼ��NS_IMAGE����
	������
		pImage	[io]:		����ʼ����NS_IMAGE����
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ��
	˵����
		ÿ��NS_IMAGE���������ֻ�ܵ���һ��NS_Image_Init����ε��ÿ��ܵ����ڴ�й¶
	*/

	NS_IMAGE_API NS_RESULT NS_Image_Destroy(NS_IMAGE *pImage);
	/*
	������
		���NS_IMAGE����
	������
		pImage	[io]:		�������NS_IMAGE����
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ��
	˵����
		ʹ����NS_IMAGE����Ҫ���ô˺������������������״̬���ʼ����һ�£��ɼ���ʹ�á�
	*/

	NS_IMAGE_API NS_RESULT NS_Image_Load(NS_IMAGE *pImage, const char *pszPath, int bKeepEnc = 0, int bDecode = 1);
	/*
	������
		���ļ���ȡͼ��
	������
		pImage	[io]:		�����ȡ����Ķ���
		pszPath	[in]:		����ͼ���ļ�·��
		bKeepEnc[in]:		����0����ɹ���ȡͼ�����pImage�б���ͼ���ԭʼ���뻺����
		bDecode	[in]:		����0�����ȡͼ�����н���
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ��
		NS_E_FORMAT		�ļ���ʽ����
		NS_E_MEMORY		�����ڴ�ʧ��
		NS_E_STORAGE_OPEN	���ļ�ʧ��
		NS_E_STORAGE_READ	��ȡ�ļ�����
		NS_E_UNSUPPORT		��֧�ֵ�ͼ���ʽ
		NS_E_FAIL			ͼ�����ʧ��
	˵����
		�ú������ļ��ж�ȡͼ�񣬽����������NS_IMAGE�ṹ�С�����ȡ�ɹ���pImage�б���ָ����Ϣ����ʧ�ܣ�pImage��ԭ�����ݻᱻ���
	*/

	NS_IMAGE_API NS_RESULT NS_Image_SetEncBuf(NS_IMAGE *pImage, const unsigned char *pEnc, int nLen, int bCopy = 0);
	/*
	������
		���ñ�������
	������
		pImage	[io]:		����������ݵ�NS_IMAGE����
		pEnc	[in]:		ָ���ı������ݻ�����
		nLen	[in]:		�������ݻ���������
		bCopy	[in]:		����0�������������ڴ棬��������ָ��������������
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ��
		NS_E_MEMORY		�����ڴ�ʧ��
	˵����
		�ú�����pImage�б���������ݻ�������Ϊ�����ṩ���ݡ��ú��������޸�ԭʼͼ�����ݻ�������
	*/

	NS_IMAGE_API NS_RESULT NS_Image_DecodeInfo(NS_IMAGE *pImage);
	/*
	������
		�Ա������ݽ��н��룬��ȡ������Ϣ��������ԭʼͼ������
	����:
		pImage	[io]:		�������ͼ�����
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ�ջ�δ���ñ��뻺����
		NS_E_UNSUPPORT		��֧�ֵ�ͼ���ʽ
		NS_E_FAIL			ͼ�����ʧ��
	˵����
		�ú����Ա������ݽ��н��룬��ȡͼ��ĸ�ʽ���������Լ�����bit��Ϣ��
	*/

	NS_IMAGE_API NS_RESULT NS_Image_Decode(NS_IMAGE *pImage, unsigned char *pRaw = NULL, int nLen = 0);
	/*
	������
		�Ա������ݽ��н��룬��ȡԭʼͼ������
	����:
		pImage	[io]:		�������ͼ�����
		pRaw	[out]:		ָ�����ԭʼͼ�����ݻ�������ָ�룬����ΪNULL
		nLen	[in]		ԭʼͼ�����ݻ��������ȣ�pRawΪNULLʱ����ֵ������
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ�ջ�δ���ñ��뻺����
		NS_E_UNSUPPORT		��֧�ֵ�ͼ���ʽ
		NS_E_BUFFER		�����ԭʼͼ�����ݻ�������С����
		NS_E_MEMORY		�����ڴ�ʧ��
		NS_E_FAIL			ͼ�����ʧ��
	˵����
		�ú����Ա������ݽ��н��룬��ȡͼ����Ϣ��ԭʼͼ�����ݡ�
		��pRaw�ǿգ������õ���ԭʼͼ�����ݽ�������ָ���Ļ������У����򣬺������ڲ�����ռ������ݡ�
	*/

	NS_IMAGE_API NS_RESULT NS_Image_SetRawBuf(NS_IMAGE *pImage, const unsigned char *pRaw, int nWidth, int nHeight, int nClrBit, int bCopy = 0);
	/*
	������
		����ԭʼͼ������
	������
		pImage	[io]:		����ԭʼͼ�����ݵ�NS_IMAGE����
		pRaw	[in]:		ָ����ԭʼͼ�����ݻ�����
		nWidth	[in]:		ԭʼͼ���
		nHeight [in]:		ԭʼͼ���
		nClrBit	[in]:		ԭʼͼ������bit
		bCopy	[in]:		����0�������������ڴ濽����ָ��������������
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ��
		NS_E_MEMORY		�����ڴ�ʧ��
	˵����
		�ú�����pImage�б���ԭʼͼ�����ݣ�ΪDecode�ṩ���ݡ��ú��������޸�ԭʼ���ݻ����������ݡ�
	*/

	NS_IMAGE_API NS_RESULT NS_Image_Encode(NS_IMAGE *pImage, NS_ImageEncodeType nEncType, const int *pnParam = NULL, unsigned char *pEnc = NULL, int nLen = 0);
	/*
	������
		��ԭʼͼ�����ݽ��б��룬��ñ�������
	������
		pImage	[io]:		�������ͼ�����
		nEncType[in]:		�����ͼ���ʽ
		pnParam	[in]:		������������˵������
		pEnc	[in]:		ָ������������ݻ�������ָ�룬����ΪNULL
		nLen	[in]:		�������ݻ��������ȣ�pEncΪNULLʱ����ֵ������
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ�ջ�δ����ԭʼͼ�����ݻ�����
		NS_E_PARAM			nEncType ��������
		NS_E_MEMORY		�����ڴ�ʧ��
		NS_E_UNSUPPORT		��֧�ֵ�ͼ���ʽ
		NS_E_BUFFER		����ı������ݻ�������С����
		NS_E_FAIL			ͼ�����ʧ��
	˵����
		�ú�����ԭʼͼ�����ݽ��б��룬��ȡ�������ݡ�
		��pEnc�ǿգ������õ������ݽ����õ���ָ���Ļ������У����򣬺������ڲ�����ռ������ݡ�
		pnParamָ���˱���ʱ�Ĳ��������ڲ�ͬ�����ʽ(nEncType)�в�ͬ���壺
			NS_IET_JPG
				pnParam[0]:	ͼ����������Χ[0,100]��Ĭ��ֵ 80
			NS_IET_J2K
				pnParam[0]:	ͼ����������Χ[0,100]��Ĭ��ֵ 70
			NS_IET_JP2
				pnParam[0]:	ͼ����������Χ[0,100]��Ĭ��ֵ 70
	*/

	NS_IMAGE_API NS_RESULT NS_Image_Gray(NS_IMAGE *pImage, unsigned char *pGray = NULL, int nLen = 0);
	/*
	������
		��BGR��ɫͼ��ת�ɻҶ�ͼ��
	������
		pImage	[io]:		��ת���ĻҶ�ͼ��
		pGray	[out]:		����Ҷ�ͼ�񻺳���
		nLen	[in]:		�Ҷ�ͼ�񻺳������ȣ�pGrayΪNULL����ֵ������
	����ֵ��
		NS_S_OK			�ɹ�
		NS_E_NULL			����ָ��Ϊ�ջ�δ����ԭʼͼ�����ݻ�����
		NS_E_BUFFER		����Ҷ�ͼ�񻺳�����С����
	˵����
		�ú�����BGR��ɫͼ��ת���ɻҶ�ͼ����pGrayΪ�գ��õ��ĻҶ�ͼ�񽫱�����ԭʼͼ�����ݻ������У�ԭ����
		��ɫͼ���ƻ���ͼ�������bit����Ϊ8����pGray��Ϊ�գ��õ��ĻҶ�ͼ�񽫱�����pGray��ָ���Ļ������У�
		pImage�����е����ݱ��ֲ��䡣
	*/

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus

class CNS_Image : public NS_IMAGE
{
public:
	CNS_Image(void)		{NS_Image_Init(this);}
	~CNS_Image()		{NS_Image_Destroy(this);}
	void Clear()		{NS_Image_Destroy(this);}
	
	NS_RESULT Load(const char *pszPath, int nKeepEnc = 0, int nDecode = 1)
	{
		return NS_Image_Load(this, pszPath, nKeepEnc, nDecode);
	}
	NS_RESULT SetEncBuf(const unsigned char *pEnc, int nLen, int nCopy = 0)
	{
		return NS_Image_SetEncBuf(this, pEnc, nLen, nCopy);
	}
	NS_RESULT DecodeInfo()
	{
		return NS_Image_DecodeInfo(this);
	}
	NS_RESULT Decode(unsigned char *pRaw = NULL, int nLen = 0)
	{
		return NS_Image_Decode(this, pRaw, nLen);
	}
	NS_RESULT SetRawBuf(const unsigned char *pRaw, int nWidth, int nHeight, int nClrBit, int bCopy = 0)
	{
		return NS_Image_SetRawBuf(this, pRaw, nWidth, nHeight, nClrBit, bCopy);
	}
	NS_RESULT Encode(NS_ImageEncodeType nEncType, const int *pnParam = NULL, unsigned char *pEnc = NULL, int nLen = 0)
	{
		return NS_Image_Encode(this, nEncType, pnParam, pEnc, nLen);
	}
	NS_RESULT Gray(unsigned char *pGray = NULL, int nLen = 0)
	{
		return NS_Image_Gray(this, pGray, nLen);
	}
};

#endif	// __cplusplus

//////////////////////////////////////////////////////////////////////////

#endif	// _NS_IMAGE_H_