/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 21:10:21
 * @link    github.com/taseikyo
 */

package main

import (
	"fmt"
	"os"
)

func main() {

	argsWithProg := os.Args
	argsWithoutProg := os.Args[1:]

	arg := os.Args[3]

	fmt.Println(argsWithProg)
	fmt.Println(argsWithoutProg)
	fmt.Println(arg)
}
