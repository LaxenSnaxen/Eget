#include <glad.h>
#include <glfw3.h>
#include <opencv.hpp>
#include <iostream>
#include <string>
#include <cxxopts.hpp>

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type

interpolate(T value_left, T value_right, T frac_right)
{
    return value_left * (1.0 - frac_right) + value_right * frac_right;
}

std::vector<std::complex<double>> genComplexSet(int sizeX, int sizeY, double realMin, double realMax, double imagMin, double imagMax)
{
    // Y axeln representerar de komplexa talen
    // X axeln representerar de reala talen

    std::vector<std::complex<double>> complexSet;

    for (int i = 0; i < sizeY; i++)
    {
        double imagInterpolationFrac = static_cast<double>(i) / (static_cast<double>(sizeY) - 1.0);
        auto imagValue = mandelbrot::interpolate(imagMin, imagMax, imagInterpolationFrac);

        for (int j = 0; j < sizeX; ++j)
        {
            double realInterpolationFrac = static_cast<double>(j) / (static_cast<double>(sizeX) - 1.0);
            auto realValue = mandelbrot::interpolate(realMin, realMax, realInterpolationFrac);

            std::complex<double> complexValue (realValue, imagValue);
            complexSet.push_back(complexValue);
        }
    }
    return complexSet;
}

std::complex<double> mandelbrotFunc(std::complex<double> zVal, std::complex<double> complexVal) 
{
    return std::pow(zVal, 2) + complexVal;
}

std::vector<int> mandelbrotSequence(const std::vector<std::complex<double>> &complexSet, double threshold, int nIterations)
{
    // Ger grå skalig färg för varje pixel i mandelbrotmängden.
    auto nValues = static_cast<int>(complexSet.size());
    
    std::vector<int> mandelbrotSet;
    mandelbrotSet.reserve(nValues);

    for (int idxValue = 0; idxValue < nValues; idxValue++)
    {
        auto complexValue = complexSet[idxValue];
        std::complex<double> zValueIterated(0.0);

        int idxIter = 0;
        for (; idxIter < nIterations; idxIter++)
        {
            // Om det är den första iterationen, använder vi fc(0) = z**2 + c.
            // Annars använder vi fc(fc(0)) eller fc(fc(fc(0))), osv...
            zValueIterated = mandelbrotFunc(zValueIterated, complexValue);

            if (std::abs(zValueIterated) > threshold)
            {
                break;
            }
        }
        if (idxIter == nIterations)
        {
            mandelbrotSet.push_back(0); // Black
        }
        else
        {
            mandelbrotSet.push_back(static_cast<int>(255 * (static_cast<double>(idxIter) / nIterations)));
        }
    }
    return mandelbrotSet;
}

namespace math_cpp_utils_opencv
{
    cv::Mat get_greyscale_mat(std::vector<int> const &greyscaleValues, int sizeX, int sizeY)
    {
        cv::Mat greyscale_mat(sizeY, sizeX, CV_8UC1);

        int idxGlobal = 0;

        for (int iRow = 0; iRow < sizeY; iRow++)
        {
            for(int jCol = 0; jCol < sizeX; ++jCol)
            {
                greyscale_mat.at<uchar>(iRow, jCol) = greyscaleValues[idxGlobal];
            }
        }
        return greyscale_mat;
    }
}

namespace timer
class timer
{
    private: 
        std::vector<std::pair<std::string, long>> timingEntries;

    public:
        void timeIt(const std::string &name, std::chrono::time_point<std::chrono::system_clock> start)
        {
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
            timingEntries.emplace_back(name, elapsed);
        }

        void logTime ()
        {
            for (auto &entry: timingEntries)
            {
                spdlog::info("'{}' executed in {} ms", entry.first, entry.second)
            }
            timingEntries.clear();
        }
}

int main(int argc, char *argv[])
{
    cxxopts::Options options{argv[0], "Mandelbrot set imag rendering tool"};
    options.add_options()
            ("w,width", "imag width", cxxopts::value<int>()->default_value("1980"))
            ("h,height", "imag height", cxxopts::value<int>()->default_value("1080"))
            ("rmin,realMin", "Real number minimum", cxxopts::value<double>()->default_value("-2.5"))
            ("rmax,realMax", "Real number maximum", cxxopts::value<double>()->default_value("1.0"))
            ("imin,imagMin", "Imaginary number minimum", cxxopts::value<double>()->default_value("-1.1"))
            ("imax,imagMax", "Imaginary number maximum", cxxopts::value<double>()->default_value("1.1"))
            ("i,nIterations", "Number of iterations", cxxopts::value<int>()->default_value("35"))
            ("t,threshold", "Abs value threshold", cxxopts::value<double>()->default_value("6.0"))
            ("p,imgP", "imag path", cxxopts::value<std::string>()->default_value("mandelbrot.png"));
    
    auto result = options.parse(argc, argv);

    auto t0 = std::chrono::high_resolution_clock::now();

    int width = result["width"].as<int>();
    int height = result["height"].as<int>();

    double realMin = ["realMin"].as<double>();
    double realMax = ["realNax"].as<double>();
    double imagMin = ["imagMin"].as<double>();
    double imagMax = ["imagReal"].as<double>();

    int nIterations = result["nIterations"].as<int>();
    double threshold = result["threshold"].as<double>();

    std::string imgName =  result["imgP"].as<std::string>();

    timer::Timer timer;

    spdlog::info("Begin mandelbrot set imag generation");

    auto t1 = std::chrono::high_resolution_clock::now();
    auto complexSet = mandelbrot::genComplexSet(width, height, realMin, realMax, imagMin, imagMax);
    time.timeIt("genComplexSet()", t1);

    // Kollar sekvens om den fortsätter in i oändlighet.
    auto t2 = std::chrono::high_resolution_clock::now();
    std::vector<int> mandelbrotSet = mandelbrot::mandelbrotSequence(complexSet, threshold, nIterations);
    time.timeIt("mandelbrotSequence()", t2);

    auto t3 = std::chrono::high_resolution_clock::now();
    cv::Mat greyscale_mat = math_cpp_utils_opencv::get_greyscale_mat(mandelbrot_set, width, height);
    timer.timeit("get_greyscale_mat()", t3);

    spdlog::info("Save imag at: {}", imgName);
    auto t4 = std::chrono::high_resolution_clock::now();
    (void) cv::imwrite(imgName, greyscale_mat);
    timer.timeit("cv::imwrite()", t4);

    timer.timeit("main()", t0);
    timer.logTime();
    return 0;
}