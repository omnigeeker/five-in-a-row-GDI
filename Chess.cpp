
void Chess::reChess(){
	int i,j;
	iWho=1;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			Platform[i][j]=0;
	iPos=0;
}
Chess::Chess(){
	int i,j;
	iWho=1;
	for(i=0;i<15;i++)
		for(j=0;j<15;j++)
			Platform[i][j]=0;
	iPos=0;
}
bool Chess::Check(Step stStep){
	if( Platform[stStep.x][stStep.y]==0 )
		return true;
	else return false;
}
bool Chess::Check(int xX,int yY){
	if( Platform[xX][yY]==0 )
		return true;
	else return false;
}
void Chess::StepNext(Step stStep){
	Platform[stStep.x][stStep.y]=stStep.who;
	aStep[iPos]=stStep;
	iPos++;
	iWho=(iWho==1)?2:1;
}
void Chess::StepNext(int _iWho,int xX,int yY){
	Platform[xX][yY]=_iWho;
	aStep[iPos].who=_iWho;
	aStep[iPos].x=xX;
	aStep[iPos].y=yY;
	iPos++;
	iWho=(iWho==1)?2:1;
}
void Chess::StepBack(){
	iPos--;
	iWho=(iWho==1)?2:1;
}