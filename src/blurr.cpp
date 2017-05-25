#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/core/version.hpp"
#if CV_MAJOR_VERSION == 3
#include "opencv2/videoio/videoio_c.h"
#endif

using namespace cv;

void blurImage(IplImage* src, IplImage* dst)
{
    blur(src, dst, Size(50, 50));
}