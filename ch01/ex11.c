/*
 * How would you test the word count program? What kinds of input are most
 * likely to uncover bugs if there are any?
 */

/*
 *
 * Answer: it doesn't cover Windows and DOS environments where RET is \r\n, it
 * also doesn't cover multibyte characters as getchar reads the value, casts it
 * to unsigned char (range 0-255) which only cover 1 byte characters, as ASCII
 *
 * the program also have a issue where it only counts lines when it meets '\n'
 *
 * it also has a issue in that special signs (!#?:$%) are treated as parts of
 * words.
 */
