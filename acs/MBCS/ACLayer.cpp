#include "ACLayer.h"

ACLayer::ACLayer()
{
}

// 레이어의 층수를 지정한다. (최대 20층)
int ACLayer::SetFloor(int n)
{
	return 0;
}

// 각 층의 이름을 지정한다. (형식적인것)
int ACLayer::SetLayerName(int n, char* name)
{
	return 0;
}

// 레이어의 층을 추가한다.
int ACLayer::InsertFloor(void)
{
	return 0;
}

// 지정한 층 다음에 층을 추가한다. (최상위층으로 추가시 0)
int ACLayer::InsertFloor(int n)
{
	return 0;
}

// 지정한 층의 위치 이동
int ACLayer::MoveFloor(int floor, int n)
{
	return 0;
}

// 레이어의 층을 제거한다.
int ACLayer::DeleteFloor(int n)
{
	return 0;
}

// 레이어제거
int ACLayer::Release(void)
{
	return 0;
}