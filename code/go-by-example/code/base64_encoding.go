/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 20:36:15
 * @link    github.com/taseikyo
 */

package main

import (
	b64 "encoding/base64"
	"fmt"
)

func main() {

	data := "abc123!?$*&()'-=@~"

	sEnc := b64.StdEncoding.EncodeToString([]byte(data))
	fmt.Println(sEnc)

	sDec, _ := b64.StdEncoding.DecodeString(sEnc)
	fmt.Println(string(sDec))
	fmt.Println()

	uEnc := b64.URLEncoding.EncodeToString([]byte(data))
	fmt.Println(uEnc)
	uDec, _ := b64.URLEncoding.DecodeString(uEnc)
	fmt.Println(string(uDec))
}
