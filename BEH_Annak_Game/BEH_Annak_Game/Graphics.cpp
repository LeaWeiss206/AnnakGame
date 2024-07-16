#include "Graphics.h"



string Graphics::parse_to_img_path(string imgName)
{
    string img_path = "C:\\Users\\1\\Desktop\\annakImages\\";
    img_path += imgName;
    img_path += ".png";
    return img_path;
}

Mat result;
Mat background;

void Graphics::printImg(vector<vector<Coordination>> const & worldGrid)
{
    vector<Mat> rows;
    for (const auto& rowPaths : worldGrid){
        vector<Mat> images;
        for (const auto& imagePath : rowPaths) {
            Mat img = imread(parse_to_img_path("TILES\\" + to_string(imagePath.tile->landTypeNumber)));
            if (img.empty()) {
                std::cerr << "Error reading image from path: " << parse_to_img_path("TILES\\"+to_string(imagePath.tile->landTypeNumber)) << std::endl;
                return;
            }
            resize(img, img, Size(30, 30));
            images.push_back(img);
        }
        cv::Mat row;
        cv::hconcat(images, row);
        rows.push_back(row);
    }
    //Mat result;
    vconcat(rows, background);
    imshow("Image Grid", background);
    result = background.clone();
    waitKey(100);
}

void Graphics::addPersonOverlay(shared_ptr<Mat> personImage, int x, int y, double d) {
    // בדיקת גבולות כדי להימנע מהוספת תמונה מחוץ לגבולות הרקע
    if (y + personImage->cols > result.cols || x + personImage->rows > result.rows) {
        std::cerr << "Person image is out of bounds!" << std::endl;
        return;
    }

    // קביעת אזור בתמונת התוצאה שבו נוסיף את תמונת ה-person
    if (d == 0.1) {
        Mat roi1 = background(Rect(y, x, personImage->cols, personImage->rows));
        addWeighted(roi1, d, *personImage, 0.5, 0.0, roi1);
    }
    /*else {
        ImageInfo imgInfo(personImage, x, y);
        movalbleImages.push_back(imgInfo);
    }*/
    Mat roi2 = result(Rect(y, x, personImage->cols, personImage->rows));
    addWeighted(roi2, d, *personImage, 0.5, 0.0, roi2); // הוספת התמונה עם שקיפות של d%
}

void Graphics::addEntityAfterBackground(const string& personImagePath, int x, int y, int size) {
    // טוענים את תמונת ה-person
    Mat img = imread(personImagePath);

    shared_ptr<Mat> person = make_shared<Mat>(img);
    if (person->empty()) {
        std::cerr << "Error reading person image from path: " << personImagePath << std::endl;
        return;
    }

    // שינוי גודל התמונה שמוסיפים אם צריך
    resize(*person, *person, Size(30*size, 30*size)); // לדוגמה, שינוי גודל ל-30x30 פיקסלים
   
    // הוספת תמונת ה-person מעל התוצאה במיקום (0, 0)
    double d;
    if (size == 1) {
        d = 0.5;
        ImageInfo imgInfo(person, x, y);
        movalbleImages.push_back(imgInfo);
    }
    else
        d = 0.1;
    addPersonOverlay(person, x*30, y*30, d);

    // הצגת התוצאה המעודכנת בחלון
    imshow("Image Grid", result);
    //waitKey(0);
}

void Graphics::moveObjectsRandomly()
{
    int i = 1, j = 1;
   /* while (waitKey(1) == -1)
    {*/
    for (ImageInfo img : movalbleImages) {
        movalbleImages[0].x = 10 * 30;
        movalbleImages[0].y = 10 * 30;
        // איפוס התוצאה לרקע המקורי
        result = background.clone();
        // הוספת כל התמונות מחדש במיקומים המעודכנים
        for (ImageInfo imgInfo : movalbleImages) {
            addPersonOverlay(imgInfo.img, imgInfo.x, imgInfo.y, 0.5);
        }
        // שמירת התוצאה המעודכנת כתמונה חדשה
        imwrite("updated_result.jpg", result);
        // הצגת התוצאה המעודכנת בחלון
        imshow("Image Grid", result);
        if (waitKey(1) != -1)
            break;
        //waitKey(0);
    }
            //addEntityAfterBackground("C:\\Users\\1\\Desktop\\annakImages\\People\\WALKING PERSON 1\\sprite_1.png", i, j, 1);
        
        /*if it's not currently moving: choose a random location in the world and instruct this object to move there.

            draw game and show
            wait(100);*/


    //}

}


