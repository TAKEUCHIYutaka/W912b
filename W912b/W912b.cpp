﻿// W912b.cpp : アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "W912b.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
WCHAR szWindowClass[MAX_LOADSTRING];    // メイン ウィンドウ クラス名

static HWND hWnd, hDlg1, hDlg2;

#define MAX_WIDTH       (4120)
#define MAX_HEIGHT      (3120)



LPCWSTR texting;
WCHAR bufF[256];
const int Nu = 3120; const int Nr = 4208;
int numu = 0; int numr = 0; int i = 0; int num = 0; int maxE = 0; int th = 0;

double t1[7][Nu][Nr];
unsigned int tem[8][Nu][Nr * 2];
unsigned int c1[Nu][Nr];
unsigned char c2[Nu][Nr];
// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Pict1Proc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    Pict2Proc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);




int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ここにコードを挿入してください。

    // グローバル文字列を初期化する
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_W912B, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // アプリケーション初期化の実行:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_W912B));

    MSG msg;

    // メイン メッセージ ループ:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_W912B));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_W912B);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス ハンドルを格納する

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      512, 256, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND  - アプリケーション メニューの処理
//  WM_PAINT    - メイン ウィンドウを描画する
//  WM_DESTROY  - 中止メッセージを表示して戻る
//
//





LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
		DragAcceptFiles(hWnd, TRUE);
		texting = TEXT("あと7ファイル取得できます。　現在0ファイル");
		break;
	
	case WM_DROPFILES:

		HDROP hdrop;
		WCHAR filename[MAX_PATH];


		hdrop = (HDROP)wParam;

		texting = TEXT("読み込んでいます");
		UpdateWindow(hWnd);

		/* ドロップされたファイルの個数を得る */
		//num = DragQueryFile(hdrop, -1, NULL, 0);
		/* ファイルを処理 */
		//for (i = 0; i < 2; i++) {
		DragQueryFile(hdrop, num, filename, sizeof(filename));
		/*
		  filename にファイル名が入っているので、ここで処理を行う。*/



		{


			fstream file;
			char buf[1];
			unsigned char bufa[1];

			file.open(filename, ios::in | ios::binary);

			while (!file.eof()) {
				file.read(buf, sizeof(buf));
				int k = 0;
				bufa[k] = buf[k];

				for (int k = 0, size = file.gcount(); k < size; ++k) {

					tem[i][numu][numr] = bufa[k];
					++numr;
					if (numr == (Nr + Nr)) {
						numr = 0;
						++numu;
					}
				}
			}
			file.close();
		}

		for (numu = 0; numu < Nu; ++numu) {
			for (numr = 0; numr < Nr; ++numr) {
				t1[i][numu][numr] = (tem[i][numu][numr * 2] + (tem[i][numu][(numr * 2) + 1]<<8));

			}
		}




		DragFinish(hdrop);
		numu = 0; numr = 0;
		i++;
		if (i == 1) {
			texting = TEXT("あと6ファイル取得できます。現在1ファイル");
		}
		else if (i == 2) {
			texting = TEXT("あと5ファイル取得できます。現在2ファイル");
		}
		else if (i == 3) {
			texting = TEXT("あと4ファイル取得できます。現在3ファイル");
		}
		else if (i == 4) {
			texting = TEXT("あと3ファイル取得できます。現在4ファイル");
		}
		else if (i == 5) {
			texting = TEXT("あと2ファイル取得できます。現在5ファイル");
		}
		else if (i == 6) {
			texting = TEXT("あと1ファイル取得できます。現在6ファイル");
		}
		
		
		
		else if (i == 7) {
			texting = TEXT("ファイル取得が完了しました。現在7ファイル");
		}
		InvalidateRect(hWnd, NULL, TRUE);
		break;



    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 選択されたメニューの解析:
            switch (wmId)
            {
			case ID_32771:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						if (i == 1) { c1[numu][numr] = t1[0][numu][numr]; }
						else if (i == 2) {c1[numu][numr] =(t1[0][numu][numr] + t1[1][numu][numr]);}
						else if (i == 3) { c1[numu][numr] = (t1[0][numu][numr] + t1[1][numu][numr] + t1[2][numu][numr]); }
						else if (i == 4) { c1[numu][numr] = (t1[0][numu][numr] + t1[1][numu][numr] + t1[2][numu][numr] + t1[3][numu][numr]); }
						else if (i == 5) { c1[numu][numr] = (t1[0][numu][numr] + t1[1][numu][numr] + t1[2][numu][numr] + t1[3][numu][numr] + t1[4][numu][numr]); }
						else if (i == 6) { c1[numu][numr] = (t1[0][numu][numr] + t1[1][numu][numr] + t1[2][numu][numr] + t1[3][numu][numr] + t1[4][numu][numr] + t1[5][numu][numr]); }
						else if (i == 7) { c1[numu][numr] = (t1[0][numu][numr] + t1[1][numu][numr] + t1[2][numu][numr] + t1[3][numu][numr] + t1[4][numu][numr] + t1[5][numu][numr] + t1[6][numu][numr]); }
						
						
					}
				}
				texting = TEXT("編集用画像を作成しました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case ID_32796:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[0][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;

			case ID_32797:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[1][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;

			case ID_32798:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[2][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;

			case ID_32799:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[3][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;

			case ID_32800:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[4][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;

			case ID_32801:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[5][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;

			case ID_32802:
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = t1[6][numu][numr]/4;
						c2[numu][numr] = c1[numu][numr];
					}
				}
				break;


			case ID_32805:
				texting = TEXT("表示準備中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);
				
				

				hDlg1 = CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW), hWnd, (DLGPROC)Pict1Proc,);


				ShowWindow(hDlg1, SW_SHOW);
				break;
			
			case ID_32806:
				texting = TEXT("表示準備中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				hDlg2=CreateDialog(hInst, MAKEINTRESOURCE(IDD_FORMVIEW),hWnd,(DLGPROC)Pict2Proc);


				

				ShowWindow(hDlg2, SW_SHOW);
				break;

			case ID_32812://最大値告知
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						if (c1[numu][numr] > maxE) {
							maxE = c1[numu][numr];
						}
					}
				}

				wsprintf(bufF,TEXT("最大値は%dです。"),maxE);
				MessageBox(hWnd, bufF, TEXT("最大値"), MB_OK);
				break;
			

				
			case ID_32807://fanc
				
				

				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						if (c1[numu][numr] < th) {
							c1[numu][numr] = 0;
						}
						
					}
				}
				
				//maxE >> 4;
				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						
							c1[numu][numr] = c1[numu][numr] << 8;
							c1[numu][numr] = c1[numu][numr] / maxE;
						
					}
				}

				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c2[numu][numr] = c1[numu][numr];
					}
				}

				maxE = 0;

				texting = TEXT("表示用画像を作成しました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case ID_32808://thr+100

				th = th + 100;
				
			
				wsprintf(bufF, TEXT("閾値を%dに設定しました。"), th);
				MessageBox(hWnd, bufF, TEXT("threshold"), MB_OK);
				break;

			case ID_32809://thr+50

				th = th + 50;


				wsprintf(bufF, TEXT("閾値を%dに設定しました。"), th);
				MessageBox(hWnd, bufF, TEXT("threshold"), MB_OK);
				break;
			case ID_32810://thr+10

				th = th + 10;


				wsprintf(bufF, TEXT("閾値を%dに設定しました。"), th);
				MessageBox(hWnd, bufF, TEXT("threshold"), MB_OK);
				break;
			case ID_32811://thr+5

				th = th + 5;


				wsprintf(bufF, TEXT("閾値を%dに設定しました。"), th);
				MessageBox(hWnd, bufF, TEXT("threshold"), MB_OK);
				break;
			case ID_32814://thr+500

				th = th + 500;


				wsprintf(bufF, TEXT("閾値を%dに設定しました。"), th);
				MessageBox(hWnd, bufF, TEXT("threshold"), MB_OK);
				break;



			case ID_32813://C

				maxE = 0;
				th = 0;

				for (numu = 0; numu < Nu; ++numu) {
					for (numr = 0; numr < Nr; ++numr) {
						c1[numu][numr] = 0;
						c2[numu][numr] = 0;
					}
				}
				texting = TEXT("編集済み画像をクリアしました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;

			case ID_32791://重ねスケール
			{
				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".ppm");
					ofn.lpstrFilter = TEXT("ppmファイル(*..ppm)\0*.ppm\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);
				}


				texting = TEXT("保存中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);


				fstream file;
				ofstream ofs(szFile);


				ofs << "P2\n#4208x3120\n4208 3120\n255\n";

				if (ofs) {
					for (numu = 0; numu < Nu; ++numu)
					{
						for (numr = 0; numr < Nr; ++numr)
						{
							if ((numu % 100 == 0) && (numr == 1)) {
								wsprintf(bufF, TEXT("3120中%d完了"), numu);
								texting = bufF;
								InvalidateRect(hWnd, NULL, FALSE);
								UpdateWindow(hWnd);
							}
							else if (numu > 3100 && numu < 3106 && numr>4030 && numr < 4155) {
								ofs << 0 << ' '; 
							}
							else if (numu > 3105 && numu < 3111 && numr>4030 && numr < 4155) {
								ofs << 255 << ' ';
							}
							else {
								c1[numu][numr] / 4;
								ofs << c1[numu][numr] << ' '; 
								if (numr == 4207)
								{
									ofs << "\n";

								}
							}
						}
					}

				}
				file.close();

			}
			texting = TEXT("保存が完了しました。");
			InvalidateRect(hWnd, NULL, TRUE);
				break;

			case ID_32792://重ねノンスケ


				static OPENFILENAME     ofn;
				static TCHAR        szPath[MAX_PATH];
				static TCHAR            szFile[MAX_PATH];

				if (szPath[0] == TEXT('\0')) {
					GetCurrentDirectory(MAX_PATH, szPath);
				}
				if (ofn.lStructSize == 0) {
					ofn.lStructSize = sizeof(OPENFILENAME);
					ofn.hwndOwner = hWnd;
					ofn.lpstrInitialDir = szPath;       // 初期フォルダ位置
					ofn.lpstrFile = szFile;       // 選択ファイル格納
					ofn.nMaxFile = MAX_PATH;
					ofn.lpstrDefExt = TEXT(".bin");
					ofn.lpstrFilter = TEXT("binファイル(*.bin)\0*.bin\0");
					ofn.lpstrTitle = TEXT("画像を保存します。");
					ofn.Flags = OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT;
				}
				if (GetSaveFileName(&ofn)) {
					MessageBox(hWnd, szFile, TEXT("ファイル名を付けて保存"), MB_OK);

				}
				texting = TEXT("保存中です。");
				InvalidateRect(hWnd, NULL, TRUE);
				UpdateWindow(hWnd);

				{
					fstream file;
					ofstream ofs(szFile);

					if (ofs) {
						for (numu = 0; numu < Nu; ++numu)
						{

							for (numr = 0; numr < Nr; ++numr)
							{
								c2[numu][numr] = c1[numu][numr];
								ofs << c2[numu][numr]; ofs << 00000000;
								if((numu%100==0)&&(numr == 1)) {
									wsprintf(bufF, TEXT("3120中%d完了"), numu);
									texting = bufF;
										InvalidateRect(hWnd, NULL, FALSE);
										UpdateWindow(hWnd);
								}
							}
						}

					}
					file.close();
				}
				texting = TEXT("保存が完了しました。");
				InvalidateRect(hWnd, NULL, TRUE);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: HDC を使用する描画コードをここに追加してください...

			TextOut(hdc, 10, 10, texting, wcslen(texting));
			
            EndPaint(hWnd, &ps);

        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


LRESULT CALLBACK Pict1Proc(HWND hDlg1, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP  hBitmap;    // ビットマップ
	static HDC      hMemDC;     // オフスクリーン
	static UINT     saveX;
	static UINT     saveY;
	static SCROLLINFO scrInfoH, scrInfoV;


	switch (message)
	{

	case WM_CLOSE:
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		DestroyWindow(hDlg1);
		break;

	case WM_INITDIALOG:
		
		HDC hDC;


		// DCコンパチブルの作成
		hDC = GetDC(hDlg1);
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, MAX_WIDTH, MAX_HEIGHT);
		SelectObject(hMemDC, hBitmap);
		ReleaseDC(hDlg1, hDC);

		for (numu = 0; numu < Nu; ++numu) {
			for (numr = 0; numr < Nr; ++numr) {


				if (numu > 3100 && numu < 3106 && numr>3930 && numr < 4056) {
					SetPixel(hMemDC, numr, numu, RGB(0,0,0));
				
				}
				else if (numu > 3105 && numu < 3111 && numr>3930 && numr < 4056) {
					SetPixel(hMemDC, numr, numu, RGB(255,255,255));
				}
				else {
					SetPixel(hMemDC, numr, numu, RGB(c2[numu][numr], c2[numu][numr], c2[numu][numr]));
				}
			}
		}


		//横スクロールバー初期設定
		scrInfoH.cbSize = sizeof(SCROLLINFO);
		scrInfoH.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoH.nMin = 0;
		scrInfoH.nMax = Nr;
		scrInfoH.nPage = 1;
		scrInfoH.nPos = 0;
		SetScrollInfo(hWnd, SB_HORZ, &scrInfoH, TRUE);

		//縦スクロールバー初期設定
		scrInfoV.cbSize = sizeof(SCROLLINFO);
		scrInfoV.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoV.nMin = 0;
		scrInfoV.nMax = Nu;
		scrInfoV.nPage = 1;
		scrInfoV.nPos = 0;
		SetScrollInfo(hWnd, SB_VERT, &scrInfoV, TRUE);



		texting = TEXT("表示しました。");
		InvalidateRect(hWnd, NULL, TRUE);

		break;
	case WM_PAINT:
		PAINTSTRUCT     ps;


		// DCコンパチブルの描画
		hDC = BeginPaint(hDlg1, &ps);
		BitBlt(hDC, 0, 0, MAX_WIDTH, MAX_HEIGHT, hMemDC, scrInfoH.nPos, scrInfoV.nPos, SRCCOPY);
		EndPaint(hDlg1, &ps);

		break;
	case WM_SIZE:
		scrInfoV.nPos = 0;
		scrInfoH.nPos = 0;
		SetScrollInfo(hDlg1, SB_HORZ, &scrInfoH, TRUE);
		SetScrollInfo(hDlg1, SB_VERT, &scrInfoV, TRUE);
		InvalidateRect(hDlg1, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			scrInfoH.nPos += 10;
			SetScrollInfo(hDlg1, SB_HORZ, &scrInfoH, TRUE);
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		case VK_LEFT:
			scrInfoH.nPos -= 10;
			SetScrollInfo(hDlg1, SB_HORZ, &scrInfoH, TRUE);
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		case VK_UP:
			scrInfoV.nPos -= 10;
			SetScrollInfo(hDlg1, SB_VERT, &scrInfoV, TRUE);
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		case VK_DOWN:
			scrInfoV.nPos += 10;
			SetScrollInfo(hDlg1, SB_VERT, &scrInfoV, TRUE);
			InvalidateRect(hDlg1, NULL, TRUE);

			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hDlg1, message, wParam, lParam);
	}
	return 0;
}



LRESULT CALLBACK Pict2Proc(HWND hDlg2, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP  hBitmap;    // ビットマップ
	static HDC      hMemDC;     // オフスクリーン
	static UINT     saveX;
	static UINT     saveY;
	static SCROLLINFO scrInfoH, scrInfoV;


	switch (message)
	{
	
	case WM_CLOSE:
		DeleteDC(hMemDC);
		DeleteObject(hBitmap);
		DestroyWindow(hDlg2);
		break;

	case WM_INITDIALOG: 
		
		HDC hDC;


		//横スクロールバー初期設定
		scrInfoH.cbSize = sizeof(SCROLLINFO);
		scrInfoH.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoH.nMin = 0;
		scrInfoH.nMax = Nr;
		scrInfoH.nPage = 1;
		scrInfoH.nPos = 0;
		SetScrollInfo(hWnd, SB_HORZ, &scrInfoH, TRUE);

		//縦スクロールバー初期設定
		scrInfoV.cbSize = sizeof(SCROLLINFO);
		scrInfoV.fMask = SIF_DISABLENOSCROLL | SIF_POS | SIF_RANGE | SIF_PAGE;
		scrInfoV.nMin = 0;
		scrInfoV.nMax = Nu;
		scrInfoV.nPage = 1;
		scrInfoV.nPos = 0;
		SetScrollInfo(hWnd, SB_VERT, &scrInfoV, TRUE);

		// DCコンパチブルの作成
		hDC = GetDC(hDlg2);
		hMemDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, MAX_WIDTH, MAX_HEIGHT);
		SelectObject(hMemDC, hBitmap);
		ReleaseDC(hDlg2, hDC);
		
			for (numu = 0; numu < Nu; ++numu) {

				for (numr = 0; numr < Nr; ++numr) {

					SetPixel(hMemDC, numr, numu, RGB(c2[numu][numr], c2[numu][numr], c2[numu][numr]));
					
				}
			}
		
		
		texting = TEXT("表示しました。");
		InvalidateRect(hWnd, NULL, TRUE);


	
		break;


	case WM_PAINT: 
		PAINTSTRUCT     ps;
		

		// DCコンパチブルの描画
		hDC = BeginPaint(hDlg2, &ps);
		BitBlt(hDC, 0, 0, MAX_WIDTH, MAX_HEIGHT, hMemDC, scrInfoH.nPos, scrInfoV.nPos, SRCCOPY);
		EndPaint(hDlg2, &ps);
	
		break;
	case WM_SIZE:
		scrInfoV.nPos = 0;
		scrInfoH.nPos = 0;
		InvalidateRect(hDlg2, NULL, TRUE);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RIGHT:
			scrInfoH.nPos += 10;
			InvalidateRect(hDlg2, NULL, TRUE);
			
			break;
		case VK_LEFT:
			scrInfoH.nPos -= 10;
			InvalidateRect(hDlg2, NULL, TRUE);
		
			break;
		case VK_UP:
			scrInfoV.nPos -= 10;
			InvalidateRect(hDlg2, NULL, TRUE);
		
			break;
		case VK_DOWN:
			scrInfoV.nPos += 10;
			InvalidateRect(hDlg2, NULL, TRUE);
		
			break;
		default:
			break;
		}

	default:
		return DefWindowProc(hDlg2, message, wParam, lParam);
	}
	return 0;
}








// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
