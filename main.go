package main

import (
	"bufio"
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func MakeSampleFile(filename string, entries int, generator *rand.Rand) error {
	file, err := os.OpenFile(filename, os.O_CREATE|os.O_WRONLY|os.O_TRUNC, 0644)
	if err != nil {
		return err
	}
	defer func() {
		file.Close()
		if err != nil {
			os.Remove(file.Name())
		}
	}()
	writer := bufio.NewWriter(file)
	for entries > 0 {
		entries--
		randomIp4 := fmt.Sprintf(
			"%d.%d.%d.%d",
			generator.Intn(256),
			generator.Intn(256),
			generator.Intn(256),
			generator.Intn(256),
		)
		row := fmt.Sprintf("%s\t%d\t%d\n", randomIp4, generator.Intn(10), generator.Intn(10))
		_, err = writer.WriteString(row)
		if err != nil {
			return err
		}
	}
	writer.Flush()
	return nil
}

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
		err = MakeSampleFile(filename, t, randomGenerator)
		if err != nil {
			fmt.Fprintln(os.Stderr, "[ERROR] message: %s", err.Error())
		}
	}
}
