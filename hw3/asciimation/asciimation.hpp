/* asciimation.hpp
   =========

   Interface definition for the Asciimation class, which generates
   Asciimation movies with an OpenCV VideoWriter.

   Part of CS70 Homework 3. This file may NOT be
   shared with anyone other than the author(s) and
   the current semester's CS70 staff without
   explicit written permission from one of the
   CS70 instructors.

 */
#ifndef ASCIIMATION_HPP_INCLUDED
#define ASCIIMATION_HPP_INCLUDED

#include <string>
#include <opencv2/opencv.hpp>
#include "sprite.hpp"

// TODO(students): Remove this line before you submit your file
#pragma GCC diagnostic ignored "-Wunused-private-field"


/**
 * \class Asciimation
 * \brief Holds the contents of an ASCIImation movie
 *
 * \details
 * Stores an array of characters that will be displayed to the screen, and
 * a Sprite that will be added to the screen.
 *
 */
class Asciimation {
 public:
   /**
    * Deletes the default constructor and adds a parameterized
    * constructor which accepts five inputs. Creates a new 
    * default constructor which accepts a reference to an 
    * Asciimation object.
   */
    Asciimation() = delete;
    Asciimation(int numRows, int numCols, int rowHeight,
                int colWidth, std::string spriteFilename);
    Asciimation(const Asciimation& other) = default;
    ~Asciimation() = default;
    Asciimation& operator = (const Asciimation& rhs) = default;

    /**
     * \brief Creates the current display showing the sprite
     * \post The current display contents are up to date and
     * ready to display to the screen.
     */
    void addFrame(cv::VideoWriter& vw);

    /**
     * \brief Scrolls a sprite across the screen by repeatedly
     * calling updateContents().
     * \post The screen is destroyed.
     */
    void generateMovie(const std::string& fname, int frameRate);

 private:
    int numRows_;
    int numCols_;
    int rowHeight_;
    int colWidth_;
    Sprite sprite_;
    int spriteCurrentRow_;
    int spriteCurrentCol_;

    static const int COLORTYPE = CV_8UC3;
    static const int FONT = cv::FONT_HERSHEY_PLAIN;
};

#endif  // ifndef ASCIIMATION_HPP_INCLUDED
