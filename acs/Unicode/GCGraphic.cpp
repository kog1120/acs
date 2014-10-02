#include "GCGraphic.h"


GCGraphic::GCGraphic(LPDIRECT3DDEVICE9 D3DDevice) : m_ImgWidth(0), m_ImgHeight(0), m_MaskColor(0, 0, 0, 255)
{
	this->D3DDevice = D3DDevice;
	SprAngle   = 0;					// 회전각을 0번으로 초기화	
	SprCenterX = 0;					// 회전 중심을 CX, CY = (0, 0)로 초기화
	SprCenterY = 0;			
	SprScaleX  = 1;					// 스케일을 SX, SY = (1, 1)로 초기화 
	SprScaleY  = 1;			
}

GCGraphic::GCGraphic()
{
}

//==================================================================================================
// ◈ LoadTexture()
// Desc : 화면 묘사
//==================================================================================================
bool GCGraphic::LoadTexture(char *Image)
{
	TCHAR	path[256];
	TCHAR	str[4]; 
	int		fp_ofst;

	// 패스의 형성
	wsprintf(path, _T("%s"), Image);

	// 확장자(extension)로부터 DDS 파일, BMP 파일을 식별
	int len = wcslen(path);
	str[0] = tolower(path[len-3]);
	str[1] = tolower(path[len-2]);
	str[2] = tolower(path[len-1]);
	str[3] = '\0';

	if (wcscmp(str, _T("bmp"))==0) {
		// BMP 파일의 19바이트째부터 이미지 데이터의 사이즈 정보가 격납된다
		fp_ofst = 18;
	} else {
		// DDS 파일의 13바이트째부터 이미지 데이터의 사이즈 정보가 격납된다
		fp_ofst = 12;
	}

	// 바이너리 모Draw 파일을 오픈해 사이즈 정보를 Road한다
	FILE *fp;
	if ((fp = fopen((const char*)path, "rb")) == NULL) return false;
	
	// 이미지 사이즈 정보까지 SEEK한다
	fseek(fp, fp_ofst, SEEK_SET);
		
	this->m_ImgWidth  |=  fgetc(fp);
	this->m_ImgWidth  |= (fgetc(fp)) << 8;
    this->m_ImgWidth  |= (fgetc(fp)) <<16;
	this->m_ImgWidth  |= (fgetc(fp)) <<24;
	
	this->m_ImgHeight |=  fgetc(fp);
	this->m_ImgHeight |= (fgetc(fp)) << 8;
	this->m_ImgHeight |= (fgetc(fp)) <<16;
	this->m_ImgHeight |= (fgetc(fp)) <<24;

	fclose(fp);

	// DDS 파일은 높이, 폭에 데이터가 차례대로 있으므로 스왑한다
	if (wcscmp(str, _T("dds"))==0) {
		unsigned int swap;
		swap = this->m_ImgWidth;
		this->m_ImgWidth = this->m_ImgHeight;
		this->m_ImgHeight = swap;
	}
	this->D3DDevice->CreateVertexBuffer(6*sizeof(VERTEX), 0, (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1), 
											D3DPOOL_DEFAULT, &m_pVB, NULL );

	D3DXCreateTextureFromFileEx(this->D3DDevice, path, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
					D3DX_FILTER_LINEAR, D3DX_FILTER_LINEAR, D3DCOLOR_RGBA(255,255,255,255), NULL, NULL, &this->m_Texture);

	return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : DrawTexture()
// Desc : 텍스쳐를 화면의 그린다.
void GCGraphic::DrawTexture(float x, float y, int u, int v, int width, int height)
{
	VERTEX VertexDataTbl[6];							//정점 정보 배열*4개
	ZeroMemory(VertexDataTbl, sizeof(VertexDataTbl));	//정점 배열을 제로 클리어

	m_x = x; m_y = y;

	// texture의 사이즈를 취득
	float w  = (float) this->m_ImgWidth; 
	float h = (float) this->m_ImgHeight;

	// texture UVWH를 픽셀 단위로부터 0~1로 변환
	float tu = (float) u / w;
	float tv = (float) v / h;
	float tw = (float) width / w;
	float th = (float) height / h;
	
	// 4 정점의 좌표를 계산
	float disp_x[4], disp_y[4];

	disp_x[0] = x;			disp_y[0] = y;			// 좌상의 정점
	disp_x[1] = x + width;	disp_y[1] = y;			// 우상의 정점
	disp_x[2] = x + width;	disp_y[2] = y + height;	// 우하의 정점
	disp_x[3] = x;			disp_y[3] = y + height;	// 좌하의 정점

/*	
	// 회전, 확대 축소 처리
	for (i=0; i<4; i++) {
		float xxx, yyy;

		// 회전, 확장 수축 중심 보정
		disp_x[i] -= (x + SprCenterX);
		disp_y[i] -= (y + SprCenterY);
		
		// 확대
		disp_x[i] *= SprScaleX;
		disp_y[i] *= SprScaleY;		

		// 회전
		xxx = disp_x[i] * (float) cos(SprAngle) - disp_y[i] * (float) sin(SprAngle);
		yyy = disp_x[i] * (float) sin(SprAngle) + disp_y[i] * (float) cos(SprAngle);		
		disp_x[i] = xxx;
		disp_y[i] = yyy;

		// 회전, 확장 수축 중심 보정
		disp_x[i] += (x + SprCenterX);
		disp_y[i] += (y + SprCenterY);
	}
//*/	

	// α블렌딩 셋
	this->D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

//	switch (SprBlend) {
//	case D3DBLEND_NORMAL:
		this->D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		this->D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	
//		break;
//	case D3DBLEND_ADD:
//		this->D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
//		this->D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		
//		break;
//	} 

	// texture를 Set
	this->D3DDevice->SetTexture(0, this->m_Texture);

	//디바이스에 사용하는 정점 포맷을 Set
	this->D3DDevice->SetFVF((D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1));

	// 우상의 3 각형을 묘화
	// 1
	VertexDataTbl[0].x     = disp_x[0];
	VertexDataTbl[0].y     = disp_y[0];
	VertexDataTbl[0].z     = 0;
	VertexDataTbl[0].rhw   = 1;
	VertexDataTbl[0].tu    = tu;
	VertexDataTbl[0].tv    = tv;
	VertexDataTbl[0].color = 0xffffffff;

	// 2
	VertexDataTbl[1].x	   = disp_x[1];
	VertexDataTbl[1].y     = disp_y[1];
	VertexDataTbl[1].z     = 0;
	VertexDataTbl[1].rhw   = 1;
	VertexDataTbl[1].tu    = tu + tw;
	VertexDataTbl[1].tv    = tv;
	VertexDataTbl[1].color = 0xffffffff;

	// 3
	VertexDataTbl[2].x	   = disp_x[2];
	VertexDataTbl[2].y	   = disp_y[2];
	VertexDataTbl[2].z	   = 0;
	VertexDataTbl[2].rhw   = 1;
	VertexDataTbl[2].tu	   = tu + tw;
	VertexDataTbl[2].tv    = tv + th;
	VertexDataTbl[2].color = 0xffffffff;
	
	// 좌상의 3 각형을 묘화
	// 1
	VertexDataTbl[3].x     = disp_x[0];
	VertexDataTbl[3].y     = disp_y[0];
	VertexDataTbl[3].z     = 0;
	VertexDataTbl[3].rhw   = 1;
	VertexDataTbl[3].tu    = tu;
	VertexDataTbl[3].tv    = tv;
	VertexDataTbl[3].color = 0xffffffff;
	
	// 2
	VertexDataTbl[4].x	   = disp_x[2];
	VertexDataTbl[4].y     = disp_y[2];
	VertexDataTbl[4].z     = 0;
	VertexDataTbl[4].rhw   = 1;
	VertexDataTbl[4].tu    = tu + tw;
	VertexDataTbl[4].tv    = tv + th;
	VertexDataTbl[4].color = 0xffffffff;
	
	// 3
	VertexDataTbl[5].x     = disp_x[3];
	VertexDataTbl[5].y     = disp_y[3];
	VertexDataTbl[5].z	   = 0;
	VertexDataTbl[5].rhw   = 1;
	VertexDataTbl[5].tu	   = tu;
	VertexDataTbl[5].tv	   = tv + th;
	VertexDataTbl[5].color = 0xffffffff;

	VOID* pVertices;
    m_pVB->Lock( 0, sizeof(VertexDataTbl), (void**)&pVertices, 0 );
    memcpy( pVertices, VertexDataTbl, sizeof(VertexDataTbl) );
    m_pVB->Unlock();

	D3DDevice->SetStreamSource( 0, m_pVB, 0, sizeof(VERTEX) );
    D3DDevice->SetFVF((D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1));
    D3DDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );
}