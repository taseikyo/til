/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 21:21:03
 * @link    github.com/taseikyo
 */

/**
 * Go 提供了一个 flag 包，支持基本的命令行标志解析
 */

package main

import (
	"flag"
	"fmt"
)

func main() {
	wordPtr := flag.String("word", "foo", "a string")

	numbPtr := flag.Int("numb", 42, "an int")
	boolPtr := flag.Bool("fork", false, "a bool")

	// 用程序中已有的参数来声明一个标志也是可以的
	// 注意在标志声明函数中需要使用该参数的指针
	var svar string
	flag.StringVar(&svar, "svar", "bar", "a string var")
	// 所有标志都声明完成以后，调用 flag.Parse() 来执行命令行解析
	flag.Parse()

	fmt.Println("word:", *wordPtr)
	fmt.Println("numb:", *numbPtr)
	fmt.Println("fork:", *boolPtr)
	fmt.Println("svar:", svar)
	fmt.Println("tail:", flag.Args())
}
