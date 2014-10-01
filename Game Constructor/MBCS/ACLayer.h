#pragma once
//==================================================================================================
//
// ▣ ACLayer.h
//
//   Name : ACLayer
//   Desc : AC를 형성하는 Layer 계층에 대해서 관리한다
//
//   Defined by : JH.K
//   Lasted 2012.05.10 02:00
//
//==================================================================================================
//
//       ┌─────┐
//       │          │  <- 최상위 층
//       ├─────┤
//       │          │
//       ├─────┤
//       │          │
//       ├─────┤
//       │          │  <- 최하위층
//		 └─────┘
//
//
class ACLayer 
{
public:
	ACLayer(void);
	int SetFloor(int); // 레이어의 층수를 지정한다. (최대 20층)
	int SetLayerName(int, char*); // 각 층의 이름을 지정한다. (형식적인것)
	int InsertFloor(void);	// 레이어의 층을 추가한다.
	int InsertFloor(int); // 지정한 층 다음에 층을 추가한다. (최상위층으로 추가시 0)
	int MoveFloor(int, int);  // 지정한 층의 위치 이동
	int DeleteFloor(int); // 레이어의 층을 제거한다.
	int Release(void); // 레이어제거

protected:

};