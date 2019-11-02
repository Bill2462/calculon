#  This file is part of measurements laboratory excercise solution.
#  Copyright (c) 2019 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
# 
#  Permission is hereby granted, free of charge, to any person obtaining a copy of
#  this software and associated documentation files (the “Software”), to deal in the
#  Software without restriction, including without limitation the rights to use, copy,
#  modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
#  and to permit persons to whom the Software is furnished to do so, subject to the
#  following conditions: THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND,
#  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
#  OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

import numpy as np
import sys

if len(sys.argv) < 2:
    print("usage: python3 genNoise.py [sample count]")
    print("Example: python3 genNoise.py 1000000")
    sys.exit(1)

LEN = int(sys.argv[1])
STD = 0.1
MEAN = 0.0
FILE_NAME = "noise.npy"

noise = np.random.normal(MEAN, STD, LEN)
np.save(FILE_NAME, noise)
