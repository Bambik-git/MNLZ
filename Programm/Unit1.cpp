//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <conio.h>
#include <iostream.h>
#include <cstdlib>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;


const float t=1e-9;
int i,j,a, i1, i2 ;
float cp, l, s, h, d, nz, dz, dtime, speed, tempstart, Ct, Cj, tempsolid, tempsredi,
templiquid, po, lampda, Q, alpha, c , db1, db2, db3, db4;
FILE * f;
int ny, nx;

/*
tempstart - ��������� ����������� ���������� ������ �����
Ct - �������� ������������ ������� �����
Cj - �������� ������������ ������ �����
tempsolid - ����������� ��������
templiquid - ����������� ���������
po - ���������
lampda - ����������� ���������������� ������ � ������� �����
Q - �������� ������� ������� �������������
cp - �������� ������������ ���������� ����
l - �����
s - ������
h - ������
d - ��� �� �������
nz - ���-�� ��������� �� ����� ������
dz - ��� �� �����
ny - ���-�� ��������� �� ������
nx - ���-�� ��������� �� ������
dtime - ��� �� �������
speed - ��������
c-����������� ������������
z - ����������
time - �����
tempsredi - ����������� ���������� �����
db1, db2, db3, db4 - ���������� ��� ���������� ��������
*/


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
Form1->ClientHeight=1080;
Form1->ClientWidth=1920;
//Form1->Name= "MNLZ";
Form1->BorderStyle=bsSingle; //��������������� ���������
Form1->Position=poScreenCenter; // ������������ ���� ������������ ������
BorderIcons = TBorderIcons() << biSystemMenu << biMinimize >> biMaximize; // ���������� ������ �������� � �� ���� �����


Ct = StrToFloat(Edit1->Text);
Cj = StrToFloat(Edit2->Text);
Q = StrToFloat(Edit19->Text);
templiquid = StrToFloat(Edit4->Text);
tempsolid = StrToFloat(Edit3->Text);
nz = StrToFloat(Edit14->Text);
h = StrToFloat(Edit11->Text);
s = StrToFloat(Edit10->Text);
d = StrToFloat(Edit13->Text);
l = StrToFloat(Edit9->Text);
po = StrToFloat(Edit5->Text);
lampda = StrToFloat(Edit6->Text);
speed = StrToFloat(Edit12->Text);
dtime = StrToFloat(Edit18->Text);
tempstart = StrToFloat(Edit8->Text);
tempsredi = StrToFloat(Edit20->Text);

cp = (Ct+Cj)/2+Q/(templiquid-tempsolid);
dz = l/nz;
ny = ceil(h/(2*d));
nx = ceil (s/(2*d));

Edit7->Text = FloatToStrF(cp, ffFixed, 5,2);
Edit15->Text = FloatToStrF(dz, ffFixed, 5,2);
Edit16->Text = FloatToStrF(ny, ffFixed, 5,2);
Edit17->Text = FloatToStrF(nx, ffFixed, 5,2);



}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{

// ������ � ������ ��� ������
f=fopen("Raschet.txt", "wt");
fprintf(f, "����� \t\t ���� ������� \t ����� \t\t ��������� \t ���� ����� \n");

float time,z =0; // ����� � ����������

Ct = StrToFloat(Edit1->Text);
Cj = StrToFloat(Edit2->Text);
Q = StrToFloat(Edit19->Text);
templiquid = StrToFloat(Edit4->Text);
tempsolid = StrToFloat(Edit3->Text);
nz = StrToFloat(Edit14->Text);
h = StrToFloat(Edit11->Text);
s = StrToFloat(Edit10->Text);
d = StrToFloat(Edit13->Text);
l = StrToFloat(Edit9->Text);
po = StrToFloat(Edit5->Text);
lampda = StrToFloat(Edit6->Text);
speed = StrToFloat(Edit12->Text);
dtime = StrToFloat(Edit18->Text);
tempstart = StrToFloat(Edit8->Text);
c=Ct;

//---------------------- �������� �� ���� � �����������

if (templiquid!=tempsolid)
        {
        cp = (Ct+Cj)/2+Q/(templiquid-tempsolid);
        Edit7->Text = FloatToStrF(cp, ffFixed, 5,2);
        }
        else
        {
        MessageBox(NULL, "����������� �������� � �������� �� ����� ���� ����������!", "��������!", MB_OK | MB_ICONWARNING);
        }

if (d && Ct && Cj && Q && templiquid && tempsolid && nz && h && s > 0)
{
dz = l/nz;
ny = ceil (h/(2*d));
nx = ceil (s/(2*d));
Edit15->Text = FloatToStrF(dz, ffFixed, 5,2);
Edit16->Text = FloatToStrF(ny, ffFixed, 5,2);
Edit17->Text = FloatToStrF(nx, ffFixed, 5,2);

}
else
{
MessageBox(NULL, "������� ���������� ������, �������� �� ����� ���� ������ ��� ����� ����", "��������!", MB_OK | MB_ICONWARNING);
}


//----------------------- �������!


StringGrid1->ColCount=nx+1;
StringGrid1->RowCount=ny+2;

 /*
    int **temp = new int* [nx];
    for (int i = 0; i < nx; i++)
    temp[i] = new int [ny];

    int **tempnext = new int* [nx];
    for (int i = 0; i < nx; i++)
    tempnext[i] = new int [ny];
   */


  //���������� �������

double temp[38][9];
double tempnext[38][9];

nx = 37 ;
ny = 8 ;

for(int i=0; i < 38; i++ )
for(int j=0; j < 9; j++ )
temp[i][j]=tempstart;

   /*
for(int i=0; i < 38; i++ )
for(int j=0; j < 9; j++ )
{
temp[i][0]=1400;
temp[37][j]=1400;
temp[36][j]=1400;
temp[35][j]=1400;
temp[34][j]=1400;
}

for(int i=0; i < 34; i++ )
for(int j=1; j < 9; j++ )
{
temp[i][1]=1420;
temp[33][j]=1420;
temp[32][j]=1420;
temp[31][j]=1420;
temp[30][j]=1420;
}


for(int i=0; i < 30; i++ )
for(int j=2; j < 9; j++ )
{
temp[i][2]=1440;
temp[29][j]=1440;
temp[28][j]=1440;
temp[27][j]=1440;
temp[26][j]=1440;
}


for(int i=0; i < 26; i++ )
for(int j=3; j < 9; j++ )
{
temp[i][3]=1460;
temp[25][j]=1460;
temp[24][j]=1460;
temp[23][j]=1460;
temp[22][j]=1460;
}


for(int i=0; i < 22; i++ )
for(int j=4; j < 9; j++ )
{
temp[i][4]=1470;
temp[21][j]=1470;
temp[20][j]=1470;
temp[19][j]=1470;
temp[18][j]=1470;
}

for(int i=0; i < 18; i++ )
for(int j=5; j < 9; j++ )
{
temp[i][5]=1480;
temp[17][j]=1480;
temp[16][j]=1480;
temp[15][j]=1480;
temp[14][j]=1480;
}

for(int i=0; i < 14; i++ )
for(int j=6; j < 9; j++ )
{
temp[i][6]=1490;
temp[13][j]=1490;
temp[12][j]=1490;
temp[11][j]=1490;
temp[10][j]=1490;
}


for(int i=0; i < 10; i++ )
for(int j=7; j < 9; j++ )
{
temp[i][7]=1500;
temp[9][j]=1500;
temp[8][j]=1500;
temp[7][j]=1500;
temp[6][j]=1500;
}

for(int i=0; i < 6; i++ )
for(int j=8; j < 9; j++ )
{
temp[i][8]=1500;
temp[5][j]=1500;
temp[4][j]=1500;
temp[3][j]=1500;
}

temp[2][8]=1510;
temp[1][8]=1510;
temp[0][8]=1510;

//temp[i][j]=1480 + rand() % 30;
 */
/*
for(int i=1; i < nx; i++ )
{
temp[i][ny]=1450;
temp[i][0] =1450;

      for(int j=1; j < ny; j++ )
       {
       temp[nx][j]=1450;
       temp[0][j]=1450;
       temp[i][j]=1500;

       }
       }

temp[0][0] = 1440;
temp[nx][0] = 1440;
temp[0][ny] = 1440;
temp[nx][ny] = 1440;
 */






//--------------------��������� �����


speed = speed/60; //��������
int a=0;
/// ���� ������� �������
while (z < l)
{
a = a+1;

/*
// ������������� ����������� �� ��� � 1

if (z < 0.5-0.05)  {
    alpha =1000;
    }
    else if (z < 1-0.05 ) {
    alpha =900;
    }
    else if (z < 2.5-0.05) {
    alpha =550;
    }
    else if (z < 6-0.05) {
    alpha =150;
    }
    else if (z < 25-0.05) {
    alpha =100;
    }
    else {
MessageBox(NULL, "������ �����", "��������!", MB_OK | MB_ICONWARNING);
    }

     */
// ������������� ����������� �� ��� � 2

/*
if (z < 0.7-0.05)  {
    alpha =1000;
    }
    else if (z < 1.5-0.05 ) {
    alpha =900;
    }
    else if (z < 2.5-0.05) {
    alpha =800;
    }
    else if (z < 6-0.05) {
    alpha =410;
    }
    else if (z < 9-0.05) {
    alpha =150;
    }
     else if (z < 26-0.05) {
     alpha =100;
    }
    else {
MessageBox(NULL, "������ �����", "��������!", MB_OK | MB_ICONWARNING);
    }
   */

// ������������� ����������� �� ��� � 3
if (z < 0.7-0.05)  {
    alpha =1000;
    }
    else if (z < 1.5-0.05 ) {
    alpha =650;
    }
    else if (z < 2.5-0.05) {
    alpha =550;
    }
    else if (z < 6-0.05) {
    alpha =420;
    }
    else if (z < 9-0.05) {
    alpha =320;
    }
     else if (z < 12-0.05) {
     alpha =220;
    }
     else if (z < 17.5-0.05) {
     alpha =100;
    }
     else if (z < 26-0.05) {
     alpha =50;
    }
    else {
MessageBox(NULL, "������ �����", "��������!", MB_OK | MB_ICONWARNING);
    }


//������� 13 ��� ������� ������� �����
for(int i=1; i < nx; i++ )
{

// -------------------������� ����������� ������������---------------------
if (temp[i][0] > templiquid) {
    c=Cj;
    }
    else if (tempsolid <=temp[i][0]  &&  temp[i][0] <=templiquid ){
    c=(Cj+Ct)/2+Q/(templiquid-tempsolid);
    }
    else if (temp[i][0]<tempsolid) {
    c=Ct;
    }

tempnext[i][0] = temp[i][0]+((lampda*dtime)/(po*c*d*d)) * (temp[i-1][0]+temp[i+1][0]+temp[i][1]-(3*temp[i][0])+(alpha*d/lampda) * (tempsredi-temp[i][0]));
StringGrid1->Cells[i+1][1]= FloatToStrF(tempnext[i][0],ffFixed,5,1);
}


//������� 14 ��� ������ ������� �����
for (int i=1; i < nx; i++ )
 {

 // -------------------������� ����������� ������������---------------------
if (temp[i][ny] > templiquid) {
    c=Cj;
    }
    else if (tempsolid <=temp[i][ny]  &&  temp[i][ny] <=templiquid ){
    c=(Cj+Ct)/2+Q/(templiquid-tempsolid);
    }
    else if (temp[i][ny]<tempsolid) {
    c=Ct;
    }

tempnext[i][ny] = temp[i][ny] + ((lampda*dtime)/(po*c*d*d))*(temp[i-1][ny]+temp[i+1][ny]+temp[i][ny-1]-3*temp[i][ny]);
StringGrid1->Cells[i+1][ny+1]=FloatToStrF (tempnext[i][ny], ffFixed,5,1);
 }

 // ������� 15 ��� ������� ����� �������� ������
for (int j=1; j < ny; j++ )
  {

  // -------------------������� ����������� ������������---------------------
if (temp[nx][j] > templiquid) {
    c=Cj;
    }
    else if (tempsolid <=temp[nx][j]  &&  temp[nx][j] <=templiquid ){
    c=(Cj+Ct)/2+Q/(templiquid-tempsolid);
    }
    else if (temp[nx][j]<tempsolid) {
    c=Ct;
    }

tempnext[nx][j] = temp[nx][j]+(lampda*dtime)/(po*c*d*d) * (temp[nx][j+1]+temp[nx][j-1]+temp[nx-1][j]-3*temp[nx][j] + (alpha*d/lampda) *(tempsredi-temp[nx][j]));
StringGrid1->Cells[nx+1][j+1]=FloatToStrF (tempnext[nx][j], ffFixed,5,1);
}

 // ������� 16 ��� ������� ���������� ����� �������� ������
for(int j=1; j < ny; j++ )
  {

  if (temp[0][j] > templiquid) {
    c=Cj;
    }
    else if (tempsolid <=temp[0][j]  &&  temp[0][j] <=templiquid ){
    c=(Cj+Ct)/2+Q/(templiquid-tempsolid);
    }
    else if (temp[0][j]>tempsolid) {
    c=Ct;
    }

tempnext[0][j] = temp[0][j] + (lampda*dtime)/(po*c*d*d) * (temp[0][j+1]+temp[0][j-1]+temp[1][j]-3*temp[0][j]);
StringGrid1->Cells[1][j+1]= FloatToStrF (tempnext[0][j], ffFixed,5,1);
 }

// ������� 12
// i = 2...nx-1
// y = 2...ny-1

for(int i=1; i < nx; i++ )
{
      for(int j=1; j < ny; j++ )
       {
       if (temp[i][j] > templiquid) {
    c=Cj;
    }
    else if (tempsolid <=temp[i][j]  &&  temp[i][j] <=templiquid ){
    c=(Cj+Ct)/2+Q/(templiquid-tempsolid);
    }
    else if (temp[i][j]<tempsolid) {
    c=Ct;
    }

tempnext[i][j] = temp[i][j] +  (lampda*dtime)/(po*c*d*d) * (temp[i-1][j]+temp[i+1][j]+temp[i][j-1]+temp[i][j+1]-4*temp[i][j]);
StringGrid1->Cells[i+1][j+1]=  FloatToStrF (tempnext[i][j], ffFixed,5,1);

       }
}

// ������ ������� ��������
tempnext[0][0] = (temp[0][1]+temp[1][0])/2;
tempnext[nx][0] = (temp[nx][1]+temp[nx-1][0])/2;
tempnext[0][ny] = (temp[0][ny-1]+temp[1][ny])/2;
tempnext[nx][ny] = (temp[nx][ny-1]+temp[nx-1][ny])/2;

// ����� ������� ��������
StringGrid1->Cells[1][1]= FloatToStrF (tempnext[0][0], ffFixed,5,1);
StringGrid1->Cells[nx+1][1]= FloatToStrF (tempnext[nx][0], ffFixed,5,1);
StringGrid1->Cells[1][ny+1]= FloatToStrF (tempnext[0][ny], ffFixed,5,1);
StringGrid1->Cells[nx+1][ny+1]= FloatToStrF (tempnext[nx][ny], ffFixed,5,1);


// �������������� �������� ��� ������ � ����
db1 = StrToFloat( StringGrid1->Cells[1][1]);
db2 = StrToFloat( StringGrid1->Cells[nx+1][1]);
db3 = StrToFloat( StringGrid1->Cells[1][ny+1]);
db4 = StrToFloat( StringGrid1->Cells[nx+1][ny+1]);



fprintf(f, "%f \t %f \t %f \t %f \t %f \n",z, db1, db2, db3, db4);   // ������ ������� �������� � ����

Series1->Add(tempnext[0][0], z, clRed );
Series2->Add(tempnext[nx][0], z, clGreen );
Series3->Add(tempnext[0][ny], z, clBlack );
Series4->Add(tempnext[nx][ny], z, clBlue );

// ���������� ����� � �������
time=time+dtime;
z=z+dtime*speed;


//��������� ���������

i1=0;
i2=0;
for (i=38; i <37*2-1; i++)
{
i1++;
i2=i2+2;
if (tempnext[i-34][8] > 1400)
{
Image1->Canvas->Pixels[i-i1][a]=RGB(255, 255, 0);
Image1->Canvas->Pixels[i-i2][a+1]=RGB(255, 255, 0);
Image1->Canvas->Pixels[i][a]=RGB(255, 255, 0);
Image1->Canvas->Pixels[i+1][a+1]=RGB(255, 255, 0);
}
else {
Image1->Canvas->Pixels[i-i1][a]=RGB(165, 42, 42 );
Image1->Canvas->Pixels[i-i2][a+1]=RGB(165, 42, 42 );
Image1->Canvas->Pixels[i][a]=RGB(165, 42, 42 );
Image1->Canvas->Pixels[i+1][a+1]=RGB(165, 42, 42 );
}
}

 a++;





//  ������������� ������� temp = tempnext
for (int i = 0; i < 38; i++)
for (int j = 0; j < 9; j++)
temp[i][j]=tempnext[i][j];

}

  /*
// �������� ��������
for (int count = 0; count < nx; count++)
        delete []temp[count];

for (int count = 0; count < nx; count++)
        delete []tempnext[count];
 */

      }

//---------------------------------------------------------------------------


void __fastcall TForm1::BitBtn1Click(TObject *Sender)
{
for (i=0; i<256; i++)
for (j=0; j<600; j++)
{
Image1->Canvas->Pixels[i][j]=RGB(0, 0, 255);
Image2->Canvas->Pixels[i][j]=RGB(0, 255, 0);
Image3->Canvas->Pixels[i][j]=RGB(255, 0, 0);
}
}
//---------------------------------------------------------------------------
