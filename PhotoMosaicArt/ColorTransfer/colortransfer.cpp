#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>
using namespace std;

vector<int> OB, OG, OR;

//カンマ区切りで読み込む関数
vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int main()
{
    int cnt = 0;
    cv::Mat img; //画像格納変数

    //元画像を2025(=45 * 45)分割して，部分ごとに画素値の中央値を記述したファイルをopen
    ifstream ifs("../OriginalProcessing/OriginalResult.csv");

    //画素値読込
    string line;
    while (getline(ifs, line)) {

        vector<string> strvec = split(line, ',');
       
        OB.push_back(stoi(strvec.at(0)));
        OG.push_back(stoi(strvec.at(1)));
        OR.push_back(stoi(strvec.at(2)));
    }

    //画像読み込み
    img = cv::imread("../OutputImage/output.jpg", 1);

    for(int ys = 0; ys < 45; ys++) {
        for(int xs = 0; xs < 45; xs++) {
            for(int y = ys * 79; y < (ys + 1) * 79; y++){
                for(int x = xs * 119; x < (xs + 1) * 119; x++) {
                    img.at<cv::Vec3b>(y, x)[0] = 0.85 * (int)img.at<cv::Vec3b>(y, x)[0] + 0.15 * (int)OB[cnt];
                    img.at<cv::Vec3b>(y, x)[1] = 0.85 * (int)img.at<cv::Vec3b>(y, x)[1] + 0.15 * (int)OG[cnt];
                    img.at<cv::Vec3b>(y, x)[2] = 0.85 * (int)img.at<cv::Vec3b>(y, x)[2] + 0.15 * (int)OR[cnt];
                }
            }
            cnt++;
        }
    }

    //MosaicArtの書き込み
    cv::imwrite("../OutputImage/output2.jpg", img);
    //MosaicArtの表示
    cv::imshow("PhotoMosaicArt",img);
    cv::waitKey(0);
}