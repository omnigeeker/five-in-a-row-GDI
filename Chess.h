typedef struct Step{
	int who;
	int x;
	int y;
}Step;
RECT rc,rcPre;
class Chess
{
private:
	int Platform[15][15];
	int iWho;
	Step aStep[15*15];
	int iPos;
	int xNow;
	int yNow;
public:
	Chess();
	void MakeRect(int xX,int yY);
	void reChess();
	bool Check(Step stStep);
	bool Check(int xX,int yY);
	int CheckWin(int _iWho,int xX,int yY);
	void StepNext(Step stStep);
	void StepNext(int _iWho,int xX,int yY);
	void StepBack();
	int DrawChess();
	int find();
	void Show(int iNum);
	int Left();
	int Right();
	int Up();
	int Down();
	int PutKey();
	void ShowTemp();
	int MouseDown(int xX,int yY);
	int MouseMove(int xX,int yY);
	void MakePreRect(int xX,int yY);
};

//Function declare
Chess::Chess()
{
	int i,j;
	iWho=1;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			Platform[i][j]=0;
	iPos=0;
	xNow=7;
	yNow=7;
	MakePreRect(xNow,yNow);
	MakeRect(xNow,yNow);
}
void Chess::reChess()
{
	int i,j;
	iWho=1;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			Platform[i][j]=0;
	iPos=0;
	xNow=7;
	yNow=7;
	MakePreRect(xNow,yNow);
	MakeRect(xNow,yNow);
}

bool Chess::Check(Step stStep)
{
	if( stStep.x>=0 && stStep.x<=14 && stStep.y>=0 && stStep.y<=14 && Platform[stStep.x][stStep.y]==0 )
		return true;
	else return false;
}
bool Chess::Check(int xX,int yY){
	if( xX>=0 && xX<=14 && yY>=0 && yY<=14 && Platform[xX][yY]==0 )
		return true;
	else return false;
}
void Chess::StepNext(Step stStep){
	xNow=stStep.x;
	yNow=stStep.y;
	Platform[stStep.x][stStep.y]=stStep.who;
	aStep[iPos]=stStep;
	iPos++;
	iWho=(iWho==1)?2:1;
	MakeRect(xNow,yNow);
}
void Chess::StepNext(int _iWho,int xX,int yY){
	xNow=xX;
	yNow=yY;
	Platform[xX][yY]=_iWho;
	aStep[iPos].who=_iWho;
	aStep[iPos].x=xX;
	aStep[iPos].y=yY;
	iPos++;
	iWho=(iWho==1)?2:1;
	MakeRect(xNow,yNow);
}
void Chess::StepBack(){
	iPos--;
	xNow=aStep[iPos].x;
	yNow=aStep[iPos].y;
	Platform[xNow][yNow]=0;
	iWho=(iWho==1)?2:1;
	MakeRect(xNow,yNow);
}
int Chess::find(){
	return iPos;
}
void Chess::Show(int iNum)
{
	int xX=aStep[iNum].x-7;
	int yY=aStep[iNum].y-7;
	if( aStep[iNum].who==1 )
	{
		hpen=(HPEN)CreatePen(PS_SOLID,0,RGB(0,0,0));
		hOldPen = (HPEN)SelectObject(hdc,hpen);
		hbrush=(HBRUSH)CreateSolidBrush( RGB(0,0,0) );
		hOldBrush = (HBRUSH)SelectObject(hdc,hbrush);
	}
	else
	{
		hpen=(HPEN)CreatePen(PS_SOLID,0,RGB(0,0,0));
		hOldPen = (HPEN)SelectObject(hdc,hpen);
		hbrush=(HBRUSH)CreateSolidBrush( RGB(255,255,255) );
		hOldBrush = (HBRUSH)SelectObject(hdc,hbrush);
	}
	Ellipse(hdc,xMid+(xX*cdLec)-cdR,yMid+(yY*cdLec)-cdR,xMid+(xX*cdLec)+cdR,yMid+(yY*cdLec)+cdR);
	SelectObject( hdc, hOldPen );
	SelectObject( hdc, hOldBrush );
	DeleteObject(hpen);
	DeleteObject(hbrush);
}
int Chess::Left(){
	int xX=xNow-1;
	if( xX<0 ) return 1;
	while( xX>0 && !Check(xX,yNow) ) xX--;
	if( xX<0 ) return 1;
	xNow=xX;
	MakeRect(xNow,yNow);
	return 1;
}
int Chess::Right()
{
	int xX=xNow+1;
	if( xX>14 ) return 1;
	while( xX<14 && !Check(xX,yNow) ) xX++;
	if( xX>14 ) return 1;
	xNow=xX;
	MakeRect(xNow,yNow);
	return 1;
}
int Chess::Up()
{
	int yY=yNow-1;
	if( yY<0 ) return 1;
	while( yY>0 && !Check(xNow,yY) ) yY--;
	if( yY<0 ) return 1;
	yNow=yY;
	MakeRect(xNow,yNow);
	return 1;
}
int Chess::Down()
{
	int yY=yNow+1;
	if( yY>14 ) return 1;
	while( yY<14 && !Check(xNow,yY) ) yY++;
	if( yY>14 ) return 1;
	yNow=yY;
	MakeRect(xNow,yNow);
	return 1;
}
int Chess::PutKey()
{
	int iWin;
	if( xNow<0 || xNow>14 || yNow<0 || yNow>14 ) 
		return 0;
	if( !Check(xNow,yNow) )
		return 0;
	iWin=CheckWin(iWho,xNow,yNow);
	StepNext(iWho,xNow,yNow);
	return iWin;
}
void Chess::ShowTemp()
{
	int xX=xNow-7;
	int yY=yNow-7;
	int _cdR=cdR+1;
	hpen = (HPEN)CreatePen(PS_SOLID,0,RGB(255,0,0));
	hOldPen = (HPEN)SelectObject(hdc,hpen);
	if( Platform[xNow][yNow]==1 )
		hbrush = (HBRUSH)CreateSolidBrush( RGB(0,0,0) );
	else if( Platform[xNow][yNow]==2 )
		hbrush = (HBRUSH)CreateSolidBrush( RGB(255,255,255) );
	else 
		hbrush = (HBRUSH)CreateSolidBrush( RGB(0,255,0) );
	hOldBrush = (HBRUSH)SelectObject(hdc,hbrush);

	Ellipse(hdc,xMid+(xX*cdLec)-_cdR,yMid+(yY*cdLec)-_cdR,xMid+(xX*cdLec)+_cdR,yMid+(yY*cdLec)+_cdR);
	SelectObject( hdc, hOldPen );
	SelectObject( hdc, hOldBrush );
	DeleteObject(hpen);
	DeleteObject(hbrush);
}
int Chess::CheckWin(int _iWho,int xX,int yY)
{
	int _xX=xX;
	int _yY=yY;
	int il1=0;
	int il2=0;

	while( _xX>0 && Platform[--_xX][_yY]==_iWho ) il1++;
	_xX=xX;
	while( _xX<14 && Platform[++_xX][_yY]==_iWho ) il2++;
	_xX=xX;
	if( il1+il2>=4 ) return _iWho;
	il1=0;
	il2=0;
	while( _xX>0 && _yY>0 && Platform[--_xX][--_yY]==_iWho ) il1++;
	_xX=xX;
	_yY=yY;


	while( _xX<14 && _yY<14 && Platform[++_xX][++_yY]==_iWho ) il2++;
	_xX=xX;
	_yY=yY;
	if( il1+il2>=4 ) return _iWho;
	il1=0;
	il2=0;


	while( _xX>0 && _yY<14 && Platform[--_xX][++_yY]==_iWho ) il1++;
	_xX=xX;
	_yY=yY;
	while( _xX<14 && _yY>0 && Platform[++_xX][--_yY]==_iWho ) il2++;
	_xX=xX;
	_yY=yY;
	if( il1+il2>=4 ) return _iWho;
	il1=0;
	il2=0;

	while( _yY>0 && Platform[_xX][--_yY]==_iWho ) il1++;
	_yY=yY;
	while( _yY<14 && Platform[_xX][++_yY]==_iWho ) il2++;
	_yY=yY;
	if( il1+il2>=4 ) return _iWho;

	return 0;
}
int Chess::MouseDown(int xX,int yY)
{
	int _xX,_yY;
	int iWin;
	_xX=(xX-xMid);
	if( _xX>0 ) _xX=(_xX+cdLec/2)/cdLec;
	else _xX=(_xX-cdLec/2)/cdLec;
	_yY=(yY-yMid);
	if( _yY>0 ) _yY=(_yY+cdLec/2)/cdLec;
	else _yY=(_yY-cdLec/2)/cdLec;

	if( _xX<-7 && _xX>7 )
		return 0;
	if( _yY<-7 && _yY>7 )
		return 0;
	if( !Check(_xX+7,_yY+7) )
		return 0;
	iWin=CheckWin(iWho,_xX+7,_yY+7);
	if( iWin )
	{
		StepNext(iWho,_xX+7,_yY+7);		
		return iWin;
	}
	StepNext(iWho,_xX+7,_yY+7);	
	return 3;
}
void Chess::MakeRect(int xX,int yY)
{
	int _xX=xX-7;
	int _yY=yY-7;
	rcPre=rc;
	rc.bottom=yMid+(_yY*cdLec)+cdLec/2;
	rc.top=yMid+(_yY*cdLec)-cdLec/2;
	rc.right=xMid+(_xX*cdLec)+cdLec/2;
	rc.left=xMid+(_xX*cdLec)-cdLec/2;
}
void Chess::MakePreRect(int xX,int yY)
{
	int _xX=xX-7;
	int _yY=yY-7;
	rcPre.bottom=yMid+(_yY*cdLec)+cdLec/2;
	rcPre.top=yMid+(_yY*cdLec)-cdLec/2;
	rcPre.right=xMid+(_xX*cdLec)+cdLec/2;
	rcPre.left=xMid+(_xX*cdLec)-cdLec/2;
}
int Chess::MouseMove(int xX,int yY)
{
	int _xX,_yY;
	int iWin;
	_xX=(xX-xMid);
	if( _xX>0 ) _xX=(_xX+cdLec/2)/cdLec;
	else _xX=(_xX-cdLec/2)/cdLec;
	_yY=(yY-yMid);
	if( _yY>0 ) _yY=(_yY+cdLec/2)/cdLec;
	else _yY=(_yY-cdLec/2)/cdLec;

	if( _xX<-7 && _xX>7 )
		return 0;
	if( _yY<-7 && _yY>7 )
		return 0;
	if( !Check(_xX+7,_yY+7) )
		return 0;
	if( xNow==_xX+7 && yNow==_yY+7 )
		return 0;
	xNow=_xX+7;
	yNow=_yY+7;
	MakeRect(xNow,yNow);
	return 1;
}
	








