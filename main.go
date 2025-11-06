package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintln(os.Stderr, "usage: file-gen n1 [... <nN>]")
		return
	}
	randomGenerator := rand.New(rand.NewSource(time.Now().Unix()))
	for i, value := range os.Args[1:] {
		t, err := strconv.Atoi(value)
		if err != nil {
			fmt.Fprintln(os.Stderr, "[ERROR] message:", err)
			continue
		}
		fmt.Printf("[%d] Generating ip_filter_test%d.tsv with %d rows\n", i, i, t)
		filename := fmt.Sprintf("ip_filter_test%d.tsv", i)
		file, err := os.OpenFile(filename, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
		if err != nil {
			fmt.Fprintln(os.Stderr, "[ERROR] message:", err)
			continue
		}
		writer := bufio.NewWriter(file)
		for t > 0 {
			t--
			randomIp4 := fmt.Sprintf(
				"%d.%d.%d.%d",
				randomGenerator.Intn(256),
				randomGenerator.Intn(256),
				randomGenerator.Intn(256),
				randomGenerator.Intn(256),
			)
			row := fmt.Sprintf("%s\t%d\t%d\n", randomIp4, randomGenerator.Intn(10), randomGenerator.Intn(10))
			_, err = writer.WriteString(row)
			if err != nil {
				fmt.Fprintln(os.Stderr, "[ERROR] message:", err)
				fmt.Fprintln(os.Stderr, "Removing file:", filename)
				file.Close()
				err = os.Remove(filename)
				if err != nil {
					fmt.Fprintln(os.Stderr, "[ERROR] message:", err)
					fmt.Fprintln(os.Stderr, "Terminating...")
					os.Exit(1)
				}
			}
		}
		writer.Flush()
		file.Close()
	}
}
