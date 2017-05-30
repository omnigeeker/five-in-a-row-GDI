void fnDrawChess(){
	int i;
	int iLast;
	POINT stPoint;

	//SetMapMode(hdc,MM_ANISOTROPIC);

	cdLow=(cxClient>cyClient)?cyClient:cxClient;
	xMid=cxClient/2;
	yMid=cyClient/2;
	cdLec=(cdLow*9/10)/15;
	cdR=cdLec/2-2;

	//Draw Platform
	
	hpen=(HPEN)CreatePen(PS_SOLID,3,RGB(0,0,255));
	hOldPen = (HPEN)SelectObject(hdc,hpen);

	for(i=-7;i<=7;i++)
	{
		MoveToEx(hdc,xMid+(i*cdLec),yMid+(-7*cdLec),&stPoint);
		LineTo(hdc,xMid+(i*cdLec),yMid+(7*cdLec));
		MoveToEx(hdc,xMid+(-7*cdLec),yMid+(i*cdLec),&stPoint);
		LineTo(hdc,xMid+(7*cdLec),yMid+(i*cdLec));
	}
	SelectObject( hdc, hOldPen );
	DeleteObject(hpen);
	//
	iLast=cChess.find();
	for(i=0;i<iLast;i++)
		cChess.Show(i);
	//
	if( !flag )
		cChess.ShowTemp();
	else
		flag = false;
}
