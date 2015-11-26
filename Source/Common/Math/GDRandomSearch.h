//
//  GDRandomSearch.h
//  GAM-1514 OSX Game
//
//  Created by Bradley Flood on 2013-11-04.
//  Copyright (c) 2013 Algonquin College. All rights reserved.
//

#ifndef __GAM_1514_OSX_Game__GDRandomSearch__
#define __GAM_1514_OSX_Game__GDRandomSearch__

#include "GDRandom.h"

class GDRandomSearch
{
public:
	GDRandomSearch(int elements);
	int getNext(bool restart = false);
	bool isDone();
	void restart();

private:
	static int s_PrimeArray[];

    GDRandom m_Rand;
	int m_Skip;
	int m_CurrentPosition;
	int m_MaxElements;
	int* m_CurrentPrime;
	int m_NumberOfSearches;
};

#endif /* defined(__GAM_1514_OSX_Game__GDRandomSearch__) */
