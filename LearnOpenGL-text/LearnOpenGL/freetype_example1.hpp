/* example1.c                                                      */
/*                                                                 */
/* This small program shows how to print a rotated string with the */
/* FreeType 2 library.                                             */

#include <stdio.h>
#include <string.h>
#include <math.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#define WIDTH 640
#define HEIGHT 480

#include "util/filesystem.h"
#include <string>

/* origin is the upper left corner */
unsigned char image[HEIGHT][WIDTH];

/* Replace this function with something useful. */

void draw_bitmap(FT_Bitmap *bitmap,
                 FT_Int x,
                 FT_Int y) {
    FT_Int i, j, p, q;
    FT_Int x_max = x + bitmap->width;
    FT_Int y_max = y + bitmap->rows;

    /* for simplicity, we assume that `bitmap->pixel_mode' */
    /* is `FT_PIXEL_MODE_GRAY' (i.e., not a bitmap font)   */

    for (i = x, p = 0; i < x_max; i++, p++) {
        for (j = y, q = 0; j < y_max; j++, q++) {
            if (i < 0 || j < 0 || i >= WIDTH || j >= HEIGHT) {
                continue;
            }
            image[j][i] |= bitmap->buffer[q * bitmap->width + p];
        }
    }
}

void show_image(std::string &fileName) {
//    int i, j;
//
//    for (i = 0; i < HEIGHT; i++) {
//        for (j = 0; j < WIDTH; j++)
//            putchar(image[i][j] == 0 ? ' ' : image[i][j] < 128 ? '+' :
//                                                                 '*');
//        putchar('\n');
//    }
    FILE *fp;
    if ((fp = fopen(fileName.c_str(), "wb+")) != nullptr) {
        int64_t written = 0;
        written += fwrite((const char *)image, sizeof(unsigned char), (size_t)(WIDTH * HEIGHT * 4), fp);
        fclose(fp);
    }
}

int freetype_example1() {
    FT_Library library;
    FT_Face face;

    FT_GlyphSlot slot;
    FT_Matrix matrix; /* transformation matrix */
    FT_Vector pen;    /* untransformed origin  */
    FT_Error error;

    const char *font_name;
    const char *text = "123";

    double angle;
    int target_height;
    int n, num_chars;

//    if (argc != 3) {
//        fprintf(stderr, "usage: %s font sample-text\n", argv[0]);
//        exit(1);
//    }

    std::string font_name1 = FileSystem::getPath("resources/fonts/Antonio-Bold.ttf");
    std::string fileName = FileSystem::getPath("LearnOpenGL-text/LearnOpenGL/dump.rgb");

    font_name = font_name1.c_str(); /* first argument     */
    num_chars = (int)strlen(text);
    angle = (25.0 / 360) * 3.14159 * 2; /* use 25 degrees     */
    target_height = HEIGHT;

    error = FT_Init_FreeType(&library); /* initialize library */
    /* error handling omitted */

    error = FT_New_Face(library, font_name, 0, &face); /* create face object */
    /* error handling omitted */

    /* use 50pt at 100dpi */
    error = FT_Set_Char_Size(face, 50 * 64, 0,
                             100, 0); /* set character size */
    /* error handling omitted */

    /* cmap selection omitted;                                        */
    /* for simplicity we assume that the font contains a Unicode cmap */

    slot = face->glyph;

    /* set up matrix */
    matrix.xx = (FT_Fixed)(cos(angle) * 0x10000L);
    matrix.xy = (FT_Fixed)(-sin(angle) * 0x10000L);
    matrix.yx = (FT_Fixed)(sin(angle) * 0x10000L);
    matrix.yy = (FT_Fixed)(cos(angle) * 0x10000L);

    /* the pen position in 26.6 cartesian space coordinates; */
    /* start at (300,200) relative to the upper left corner  */
    pen.x = 300 * 64;
    pen.y = (target_height - 200) * 64;

    for (n = 0; n < num_chars; n++) {
        /* set transformation */
        FT_Set_Transform(face, &matrix, &pen);

        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Char(face, text[n], FT_LOAD_RENDER);
        if (error)
            continue; /* ignore errors */

        /* now, draw to our target surface (convert position) */
        draw_bitmap(&slot->bitmap,
                    slot->bitmap_left,
                    target_height - slot->bitmap_top);

        /* increment pen position */
        pen.x += slot->advance.x;
        pen.y += slot->advance.y;
    }

    show_image(fileName);

    FT_Done_Face(face);
    FT_Done_FreeType(library);

    return 0;
}

/* EOF */
