#pragma once

#include <utility>
#include <vector>

#define SHIFT 50
#define ENDX 600

class CCoordinates
{
public:
	CCoordinates( /*CPen* pPen*/std::pair<int, int> leftTop, std::pair<int, int> rightBottom );
	CCoordinates( std::pair<int, int> leftTop, std::pair<int, int> rightBottom, std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> cLines2 );
	
	~CCoordinates();

public:
	void drawCoordinates( CDC * pDC );

private:
	CPen* getCPen();

private:
	CPen* m_pPen;
	std::pair<int, int> leftTop;
	std::pair<int, int> rightBottom;
	/////////////////////
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> lines2;


};

