/**
 * @authors Lewis Tian (taseikyo@gmail.com)
 * @date    2021-01-26 20:03:09
 * @link    github.com/taseikyo
 */

/**
 * Defer 用于确保程序在执行完成后，会调用某个函数，一般是执行清理工作
 * Defer 的用途跟其他语言的 ensure 或 finally 类似
 */

package main

import (
	"fmt"
	"os"
)

func main() {

	f := createFile("/tmp/defer.txt")
	defer closeFile(f)
	writeFile(f)
}

func createFile(p string) *os.File {
	fmt.Println("creating")
	f, err := os.Create(p)
	if err != nil {
		panic(err)
	}
	return f
}

func writeFile(f *os.File) {
	fmt.Println("writing")
	fmt.Fprintln(f, "data")

}

func closeFile(f *os.File) {
	fmt.Println("closing")
	err := f.Close()

	if err != nil {
		fmt.Fprintf(os.Stderr, "error: %v\n", err)
		os.Exit(1)
	}
}
