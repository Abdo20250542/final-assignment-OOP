// عمرو احمد طه شيحه         20250449   filter  (2-6)
// جابر اكرامي جابر الزغبي   20250140  filter (1-5)
// كريم محمد السيد سليمان    20250490  filter (3-7)
// محمد اشرف فتحي عبدالمقصود                  20250542  filter (4-8)
#include <iostream>
#include "Image_class.h"
using namespace std;
// f1 done
void Grayscale(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {

        for (int j = 0; j < work_on.height; j++)
        {
            int mid = (work_on(i, j, 0) + work_on(i, j, 1) + work_on(i, j, 2)) / 3;

            for (int k = 0; k < work_on.channels; k++)
            {
                work_on(i, j, k) = mid;
            }
        }
    }
}
// F2 done
void BlackAndWhite(Image &work_on)
{
    for (int i = 0; i < work_on.width; i++)
    {
        for (int j = 0; j < work_on.height; j++)
        {
            int mid = (work_on(i, j, 0) + work_on(i, j, 1) + work_on(i, j, 2)) / 3;
            mid = (mid > 255 / 2.2 ? 255 : 0);

            work_on(i, j, 0) = mid;
            work_on(i, j, 1) = mid;
            work_on(i, j, 2) = mid;
        }
    }
}
// F3 done
Image Invert(Image &input)
{
    // Image work_on(input.width, input.height);

    for (int y = 0; y < input.height; y++)
    {
        for (int x = 0; x < input.width; x++)
        {
            unsigned char R_new = 255 - input(x, y, 0);
            unsigned char G_new = 255 - input(x, y, 1);
            unsigned char B_new = 255 - input(x, y, 2);

            input(x, y, 0) = R_new;
            input(x, y, 1) = G_new;
            input(x, y, 2) = B_new;
        }
    }

    return input;
}
// F4 sime done  (مع زخارف ولا عادي)
void AddFrame(Image &work_on)
{
    for (int i = 0; i < work_on.width; ++i)
    {
        for (int j = 0; j < work_on.height; ++j)
        {
            if (i <= 20 || j <= 25 || work_on.width - i <= 20 || work_on.height - j <= 25)
            {
                work_on(i, j, 0) = 255;
                work_on(i, j, 1) = 255;
                work_on(i, j, 2) = 255;
            }
        }
    }
}
// F5 done (ask عمودي ولا افقي)
void Flip(Image &work_on)
{
    int karar;
    cout << "1. horizontal";
    cout << "2. vertical";
    cin >> karar;
    if (karar == 1)
    {
        for (int j = work_on.width / 2; j < work_on.width; j++)
        {
            for (int i = 0; i < work_on.height; i++)
            {
                for (int k = 0; k < work_on.channels; k++)
                {
                    int temp = work_on(j, i, k);
                    work_on(j, i, k) = work_on((work_on.width - 1) - j, i, k);
                    work_on((work_on.width - 1) - j, i, k) = temp;
                }
            }
        }
    }
    else
    {
        for (int j = work_on.height / 2; j < work_on.height; j++)
        {
            for (int i = 0; i < work_on.width; i++)
            {
                for (int k = 0; k < work_on.channels; k++)
                {
                    int temp = work_on(j, i, k);
                    work_on(j, i, k) = work_on((work_on.height - 1) - j, i, k);
                    work_on((work_on.height - 1) - j, i, k) = temp;
                }
            }
        }
    }
}
// F6 done
Image Rotate(Image &work_on)
{
    Image Roty(work_on.height, work_on.width);

    for (int i = 0; i < work_on.width; ++i)
    {
        for (int j = 0; j < work_on.height; ++j)
        {
            int RX = work_on.height - 1 - j;
            int RY = i;

            for (int k = 0; k < 3; ++k)
            {
                Roty(RX, RY, k) = work_on(i, j, k);
            }
        }
    }
    return Roty;
}
// F7 done
Image DarkenAndLighten(Image &input, bool darken)
{
    Image output(input.width, input.height);

    for (int y = 0; y < input.height; y++)
    {
        for (int x = 0; x < input.width; x++)
        {
            unsigned char r = input(x, y, 0);
            unsigned char g = input(x, y, 1);
            unsigned char b = input(x, y, 2);

            unsigned char R_new;
            unsigned char G_new;
            unsigned char B_new;

            if (!darken)
            {
                R_new = r * 0.5;
                G_new = g * 0.5;
                B_new = b * 0.5;
            }
            else
            {
                R_new = r * 1.5 > 255 ? 255 : r * 1.5;
                G_new = g * 1.5 > 255 ? 255 : g * 1.5;
                B_new = b * 1.5 > 255 ? 255 : b * 1.5;
            }

            output(x, y, 0) = R_new;
            output(x, y, 1) = G_new;
            output(x, y, 2) = B_new;
        }
    }

    return output;
}
// F8 noooooooo
void Resize(Image &work_on, float W, float H)
{
}

int main()
{
    string fname, newname, dec;
    bool flag = true, OnlyFirstTime = false;
    cout << "Enter the name of the image file: ";
    cin >> fname;
    Image img("luffy.jpg");
    Image work_on("luffy.jpg");
    do
    {
        if (OnlyFirstTime)
        {
            string crt;
            cout << "would you like to contenue on current image or back to old?  type(crt/old)\n";
            cin >> crt;
            if (crt == "old")
            {
                work_on = img;
            }
        }

        cout << "1-Grayscale_Filter" << endl;
        cout << "2-Black and White_Filter" << endl;
        cout << "3-Invert Image_Filter" << endl;
        cout << "4-Adding a Frame to the Picture" << endl;
        cout << "5-Flip Image_Filter" << endl;
        cout << "6-Rotate Image_Filter" << endl;
        cout << "7-Darken and Lighten Image_Filter" << endl;
        cout << "8-Resizing Images_Filter" << endl;

        int choice;
        cin >> choice;

        if (choice == 1)
        {
            Grayscale(work_on);
        }
        else if (choice == 2)
        {
            BlackAndWhite(work_on);
        }
        else if (choice == 3)
        {
            work_on = Invert(work_on);
        }
        else if (choice == 4)
        {
            AddFrame(work_on);
        }
        else if (choice == 5)
        {
            Flip(work_on);
        }
        else if (choice == 6)
        {
            int num;
            cout << "how many times to rotate? \n";
            cin >> num;
            while (num--)
            {
                work_on = Rotate(work_on);
            }
        }
        else if (choice == 7)
        {
            int type = 0;
            cout << "1. Darken\n";
            cout << "2. Lighten\n";
            cin >> type;

            work_on = DarkenAndLighten(work_on, type - 1);
        }
        else if (choice == 8)
        {
            int W, H;
            cout << "enter new width and hight : \n ";
            cin >> W >> H;
            Resize(work_on, W, H);
        }
        cout << "DONE\n";
        cout << "want to save image?   type(yes/no)\n";
        cin >> dec;
        if (dec[0] == 'y' || dec[0] == 'Y')
        {
            cout << "enter the file name & type which you want to save the new image in: \n";
            cout << "same name will cause an overload\n ";
            cin >> newname;
            work_on.saveImage("n.jpg");
        }
        cout << "contenue or exit?   type(\"exit\" to exit)\n";
        cin >> dec;
        if (dec[0] == 'e' || dec[0] == 'E')
            flag = false;

        OnlyFirstTime = true;

    } while (flag);

    cout << "Thanks for using our photoshop app";
    return 0;
}
