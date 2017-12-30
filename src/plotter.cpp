/**************************************************************************
 *                                                                        *
 *   Author: Ivo Filot <i.a.w.filot@tue.nl>                               *
 *                                                                        *
 *   EDP is free software:                                                *
 *   you can redistribute it and/or modify it under the terms of the      *
 *   GNU General Public License as published by the Free Software         *
 *   Foundation, either version 3 of the License, or (at your option)     *
 *   any later version.                                                   *
 *                                                                        *
 *   EDP is distributed in the hope that it will be useful,               *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty          *
 *   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.              *
 *   See the GNU General Public License for more details.                 *
 *                                                                        *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program.  If not, see http://www.gnu.org/licenses/.  *
 *                                                                        *
 **************************************************************************/

#include "plotter.h"

Plotter::Plotter(unsigned int _width, unsigned int _height) {
    this->scheme = new ColorScheme(0, 10, 0);

    this->width = _width;
    this->height = _height;

    this->surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, this->width, this->height);
    this->cr = cairo_create (this->surface);

    this->set_background(Color(255, 252, 213));
}

/*
 * Sets the background color of the image
 */
void Plotter::set_background(const Color &_color) {
    cairo_set_source_rgb(this->cr, _color.get_r(), _color.get_g(), _color.get_b());
    cairo_rectangle(this->cr, 0, 0, this->width, this->height);
    cairo_fill(this->cr);
}

/*
 * Draws a line. The position xstop and ystop are the ending positions of the line
 * and *not* the direction of the line.
 */
void Plotter::draw_line(float xstart, float ystart, float xstop, float ystop,
                        const Color &_color, float line_width) {
    cairo_set_source_rgb(this->cr, _color.get_r(), _color.get_g(), _color.get_b());
    cairo_move_to(this->cr, xstart, ystart);
    cairo_line_to(this->cr, xstop, ystop);
    cairo_set_line_width(this->cr, line_width);
    cairo_stroke(this->cr);
}

/*
 * Create a filled rectangle. That is a rectangle without a border.
 */
void Plotter::draw_filled_rectangle(float xstart, float ystart, float xstop, float ystop,
                                    const Color &_color) {
    cairo_set_source_rgb(this->cr, _color.get_r(), _color.get_g(), _color.get_b());
    cairo_rectangle (this->cr, xstart, ystart, xstop, ystop);
    cairo_fill(this->cr);
}

/*
 * Create an empty rectangle. In other words, just the border of the rectangle.
 */
void Plotter::draw_empty_rectangle(float xstart, float ystart, float xstop, float ystop,
                                   const Color &_color, float line_width) {
    cairo_set_source_rgb(this->cr, _color.get_r(), _color.get_g(), _color.get_b());
    cairo_rectangle (this->cr, xstart, ystart, xstop, ystop);
    cairo_set_line_width(this->cr, line_width);
    cairo_stroke(this->cr);
}

/*
 * Create a filled circle. That is a circle without a border.
 */
void Plotter::draw_filled_circle(float cx, float cy, float radius,
                                 const Color &_color) {
    cairo_set_source_rgb(this->cr, _color.get_r(), _color.get_g(), _color.get_b());
    cairo_arc(this->cr, cx, cy, radius, 0.0, 2 * M_PI);
    cairo_fill(this->cr);
}

/*
 * Create an empty circle. In other words, just the border of the circle.
 */
void Plotter::draw_empty_circle(float cx, float cy, float radius,
                                const Color &_color, float line_width) {
    cairo_set_source_rgb(this->cr, _color.get_r(), _color.get_g(), _color.get_b());
    cairo_arc(this->cr, cx, cy, radius, 0.0, 2 * M_PI);
    cairo_set_line_width(this->cr, line_width);
    cairo_stroke(this->cr);
}

void Plotter::write(const char* filename) {
  cairo_surface_write_to_png(this->surface, filename);
}

/**************************************************************************
 *                                                                        *
 *   Color scheme and colors                                              *
 *                                                                        *
 **************************************************************************/

/**
 * Constructor
 *
 * Define lower and upper boundary of the color scheme. The colorscheme will
 * generate only colors by interpolation if the requested value to be colorcoded
 * is within the boundaries set here.
 *
 */
ColorScheme::ColorScheme(double _low, double _high, unsigned int scheme_id) {
    this->low = _low;
    this->high = _high;
    this->construct_scheme(scheme_id);
    this->convert_scheme();
}

/**
 *
 * Construct a colorscheme. The color values are here hardcoded and extracted from:
 * http://colorbrewer2.org/
 *
 */
void ColorScheme::construct_scheme(unsigned int scheme_id) {
    switch(scheme_id) {
        case 0: // http://colorbrewer2.org/#type=diverging&scheme=RdBu&n=11
            this->scheme.push_back("053061");
            this->scheme.push_back("2166ac");
            this->scheme.push_back("4393c3");
            this->scheme.push_back("92c5de");
            this->scheme.push_back("d1e5f0");
            this->scheme.push_back("f7f7f7");
            this->scheme.push_back("fddbc7");
            this->scheme.push_back("f4a582");
            this->scheme.push_back("d6604d");
            this->scheme.push_back("b2182b");
            this->scheme.push_back("67001f");
        break;
        case 1: // http://colorbrewer2.org/#type=sequential&scheme=YlGnBu&n=9
            this->scheme.push_back("ffffd9");
            this->scheme.push_back("edf8b1");
            this->scheme.push_back("c7e9b4");
            this->scheme.push_back("7fcdbb");
            this->scheme.push_back("41b6c4");
            this->scheme.push_back("1d91c0");
            this->scheme.push_back("225ea8");
            this->scheme.push_back("253494");
            this->scheme.push_back("081d58");
        break;
        case 2: // http://colorbrewer2.org/#type=diverging&scheme=BrBG&n=11
            this->scheme.push_back("543005");
            this->scheme.push_back("8c510a");
            this->scheme.push_back("bf812d");
            this->scheme.push_back("dfc27d");
            this->scheme.push_back("f6e8c3");
            this->scheme.push_back("f5f5f5");
            this->scheme.push_back("c7eae5");
            this->scheme.push_back("80cdc1");
            this->scheme.push_back("35978f");
            this->scheme.push_back("01665e");
            this->scheme.push_back("003c30");
        break;
        case 3: // http://colorbrewer2.org/#type=diverging&scheme=PiYG&n=11
            this->scheme.push_back("8e0152");
            this->scheme.push_back("c51b7d");
            this->scheme.push_back("de77ae");
            this->scheme.push_back("f1b6da");
            this->scheme.push_back("fde0ef");
            this->scheme.push_back("f7f7f7");
            this->scheme.push_back("e6f5d0");
            this->scheme.push_back("b8e186");
            this->scheme.push_back("7fbc41");
            this->scheme.push_back("4d9221");
            this->scheme.push_back("276419");
        break;
        case 4: // http://colorbrewer2.org/#type=diverging&scheme=RdYlGn&n=11
            this->scheme.push_back("a50026");
            this->scheme.push_back("d73027");
            this->scheme.push_back("f46d43");
            this->scheme.push_back("fdae61");
            this->scheme.push_back("fdae61");
            this->scheme.push_back("ffffbf");
            this->scheme.push_back("d9ef8b");
            this->scheme.push_back("a6d96a");
            this->scheme.push_back("66bd63");
            this->scheme.push_back("1a9850");
            this->scheme.push_back("006837");
        break;
        case 5: // http://colorbrewer2.org/#type=sequential&scheme=PuBuGn&n=9
            this->scheme.push_back("fff7fb");
            this->scheme.push_back("ece2f0");
            this->scheme.push_back("d0d1e6");
            this->scheme.push_back("a6bddb");
            this->scheme.push_back("67a9cf");
            this->scheme.push_back("3690c0");
            this->scheme.push_back("02818a");
            this->scheme.push_back("016c59");
            this->scheme.push_back("014636");
        break;
        case 6: http://colorbrewer2.org/#type=sequential&scheme=RdPu&n=9
            this->scheme.push_back("fff7f3");
            this->scheme.push_back("fde0dd");
            this->scheme.push_back("fcc5c0");
            this->scheme.push_back("fa9fb5");
            this->scheme.push_back("f768a1");
            this->scheme.push_back("dd3497");
            this->scheme.push_back("ae017e");
            this->scheme.push_back("7a0177");
            this->scheme.push_back("49006a");
        break;
        case 7: // http://tristen.ca/hcl-picker/#/hlc/6/1.05/CAF270/453B52
            this->scheme.push_back("CAF270");
            this->scheme.push_back("73D487");
            this->scheme.push_back("30B097");
            this->scheme.push_back("288993");
            this->scheme.push_back("41607A");
            this->scheme.push_back("453B52");
        break;
        case 8: // http://tristen.ca/hcl-picker/#/hlc/6/1.05/80C5F4/411D1E
            this->scheme.push_back("80C5F4");
            this->scheme.push_back("929ACB");
            this->scheme.push_back("92729C");
            this->scheme.push_back("824F6B");
            this->scheme.push_back("653340");
            this->scheme.push_back("411D1E");
        break;
        case 9: // http://tristen.ca/hcl-picker/#/hlc/6/1/21313E/EFEE69
            this->scheme.push_back("21313E");
            this->scheme.push_back("20575F");
            this->scheme.push_back("268073");
            this->scheme.push_back("53A976");
            this->scheme.push_back("98CF6F");
            this->scheme.push_back("EFEE69");
        break;
        case 10: // http://tristen.ca/hcl-picker/#/clh/6/253/134695/D8C8BC
            this->scheme.push_back("D8C8BC");
            this->scheme.push_back("B4ABC5");
            this->scheme.push_back("8F90C5");
            this->scheme.push_back("6876BD");
            this->scheme.push_back("415DAD");
            this->scheme.push_back("134695");
        break;
        case 11: // http://tristen.ca/hcl-picker/#/clh/6/253/134695/D8C8BC
            this->scheme.push_back("134695");
            this->scheme.push_back("415DAD");
            this->scheme.push_back("6876BD");
            this->scheme.push_back("8F90C5");
            this->scheme.push_back("B4ABC5");
            this->scheme.push_back("D8C8BC");
        break;
        case 12: // http://gka.github.io/palettes/#diverging|c0=darkred,deeppink,lightyellow|c1=lightyellow,lightgreen,teal|steps=13|bez0=1|bez1=1|coL0=1|coL1=1
            this->scheme.push_back("008080");
            this->scheme.push_back("399785");
            this->scheme.push_back("5aaf8c");
            this->scheme.push_back("7ac696");
            this->scheme.push_back("9edba4");
            this->scheme.push_back("c7f0ba");
            this->scheme.push_back("ffffe0");
            this->scheme.push_back("ffd1c9");
            this->scheme.push_back("fea0ac");
            this->scheme.push_back("ef738b");
            this->scheme.push_back("d84765");
            this->scheme.push_back("b61d39");
            this->scheme.push_back("8b0000");
        break;
        case 13: // http://gka.github.io/palettes/#diverging|c0=darkred,lightyellow|c1=lightyellow,lightgreen,teal|steps=13|bez0=1|bez1=1|coL0=1|coL1=1
            this->scheme.push_back("008080");
            this->scheme.push_back("399785");
            this->scheme.push_back("5aaf8c");
            this->scheme.push_back("7ac696");
            this->scheme.push_back("9edba4");
            this->scheme.push_back("c7f0ba");
            this->scheme.push_back("ffffe0");
            this->scheme.push_back("f1d7b7");
            this->scheme.push_back("e2b08f");
            this->scheme.push_back("cf8a69");
            this->scheme.push_back("bb6345");
            this->scheme.push_back("a43c23");
            this->scheme.push_back("8b0000");
        break;
        default:
            this->scheme.push_back("053061");
            this->scheme.push_back("2166ac");
            this->scheme.push_back("4393c3");
            this->scheme.push_back("92c5de");
            this->scheme.push_back("d1e5f0");
            this->scheme.push_back("f7f7f7");
            this->scheme.push_back("fddbc7");
            this->scheme.push_back("f4a582");
            this->scheme.push_back("d6604d");
            this->scheme.push_back("b2182b");
            this->scheme.push_back("67001f");
        break;
    }
}

/**
 *
 * Convert the colorscheme set in hexidecimal RGB to integer RGB
 *
 */
void ColorScheme::convert_scheme() {
    for(unsigned int i=0; i<this->scheme.size(); i++) {
        this->colors.push_back(this->rgb2color(this->scheme[i]));
    }
}

/**
 *
 * Convert string of hexidecimal RGB values to three integers
 *
 */
Color ColorScheme::rgb2color(const std::string &_hex) {
    return Color(this->hex2int(_hex.substr(0,2)),
                 this->hex2int(_hex.substr(2,2)),
                 this->hex2int(_hex.substr(4,2)));
}

/**
 *
 * Return a color by interpolation by supplying a value
 *
 */
Color ColorScheme::get_color(double _value) {

    if(_value > this->high) {
        return this->colors.back();
    }
    if(_value < this->low) {
        return this->colors.front();
    }

    float binsize = ((this->high - this->low)/(double)(this->colors.size()-1));
    unsigned int bin = floor((_value - this->low) / binsize);

    // interpolate between the two colors
    float residual = (_value - this->low - (float)bin * binsize) / binsize;

    float r = residual * this->colors[bin+1].get_r() + (1.0-residual) * this->colors[bin].get_r();
    float g = residual * this->colors[bin+1].get_g() + (1.0-residual) * this->colors[bin].get_g();
    float b = residual * this->colors[bin+1].get_b() + (1.0-residual) * this->colors[bin].get_b();

    return Color(r*255,g*255,b*255);
}

/**
 *
 * Convert a single hexidecimal value to an integer
 *
 */
unsigned int ColorScheme::hex2int(const std::string &_hex) {
    char* offset;
    if(_hex.length() > 2) {
        if(_hex[0] == '0' && _hex[1] == 'x') {
            return strtol(_hex.c_str(), &offset, 0);
        }
    }
    return strtol(_hex.c_str(), &offset, 16);
}

/**
 *
 * Color constructor
 *
 */
Color::Color(unsigned int _r, unsigned int _g, unsigned int _b) {
    this->r = _r;
    this->g = _g;
    this->b = _b;
}

/**
 *
 * Return the integer value for red (divide by 255 because we want on the [0,1] interval)
 *
 */
float Color::get_r() const {
    return this->r / 255.0f;
}

/**
 *
 * Return the integer value for green (divide by 255 because we want on the [0,1] interval)
 *
 */
float Color::get_g() const {
    return this->g / 255.0f;
}

/**
 *
 * Return the integer value for blue (divide by 255 because we want on the [0,1] interval)
 *
 */
float Color::get_b() const {
    return this->b / 255.0f;
}
