/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 20:34:30
 * @link    github.com/taseikyo
 */

package main

import (
	"crypto/sha1"
	"fmt"
)

func main() {
	s := "sha1 this string"

	h := sha1.New()

	h.Write([]byte(s))

	bs := h.Sum(nil)

	fmt.Println(s)
	fmt.Printf("%x\n", bs)
}
