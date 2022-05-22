////#include "AIprocessing.h"
////
////EndPosiotion::EndPosiotion(int rot, int pos, ColorsType shape)
////{
////	this->rotation = rot;
////	this->x = pos;
////	this->shape = shape;
////}
////
////AIprocessing::AIprocessing(Stack &s)
////{
////	this->cur = s;
////}
////
////void AIprocessing::CalculateEndPositionArray()
////{
////	endPositions = new EndPosiotion(GetRot() ,GetLeftXInd(), 
////		cur.curpiece->getColorPiece())[];
////}
////
////int AIprocessing::GetLeftXInd()
////{
////	int min = 11;
////	for (int i = 0; i < 4; i++)
////	{
////		if (min < cur.curpiece->tetromino[i]->x)
////			min = cur.curpiece->tetromino[i]->x;
////	}
////
////	return min;
////}
////
////int AIprocessing::GetRot()
////{
////	if(cur.curpiece->getColorPiece())
////	return 0;
////}
////
////int AIprocessing::GetMaximumXInARow()
////{
////	return 0;
////}
