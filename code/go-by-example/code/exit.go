/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 21:49:37
 * @link    github.com/taseikyo
 */

/**
 * 当使用 os.Exit 时 defer 将不会 被执行
 * 所以 fmt.Println 将永远不会被调用
 */

package main

import (
	"fmt"
	"os"
)

func main() {

	defer fmt.Println("!")

	os.Exit(3)
}
