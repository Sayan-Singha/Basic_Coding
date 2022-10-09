# Python3 program that performs the following
# operations: Sort elements by frequency. If two elements
# have same count, then put the elements that appears first

# Used for sorting


class ele:
	def __init__(self):

		self.count = 0
		self.index = 0
		self.val = 0


def mycomp(a):
	return a.val

# Used for sorting by frequency. And if frequency is same,
# then by appearance


def mycomp2(a):
	# using negative value for a.index
	# since the sorting should be in
	# descending order
	return (a.count, -a.index)


def sortByFrequency(arr, n):
	element = [None for _ in range(n)]
	for i in range(n):

		element[i] = ele()

		# Fill Indexes
		element[i].index = i

		# Initialize counts as 0
		element[i].count = 0

		# Fill values in structure
		# elements
		element[i].val = arr[i]

	# Sort the structure elements according to value,
	# we used stable sort so relative order is maintained.
	#
	element.sort(key=mycomp)

	# initialize count of first element as 1
	element[0].count = 1

	# Count occurrences of remaining elements
	for i in range(1, n):

		if (element[i].val == element[i - 1].val):
			element[i].count += element[i - 1].count + 1

			# Set count of previous element as -1, we are
			# doing this because we'll again sort on the
			# basis of counts (if counts are equal than on
			# the basis of index)*/
			element[i - 1].count = -1

			# Retain the first index (Remember first index
			# is always present in the first duplicate we
			# used stable sort. */
			element[i].index = element[i - 1].index

		# Else If previous element is not equal to current
		# so set the count to 1
		else:
			element[i].count = 1

	# Now we have counts and first index for each element
	# so now sort on the basis of count and in case of tie
	# use index to sort.*/
	element.sort(key=mycomp2)

	index = 0
	for i in range(n - 1, -1, -1):
		if (element[i].count != -1):
			for j in range(element[i].count):
				arr[index] = element[i].val
				index += 1


# Driver code
arr = [2, 5, 2, 6, -1, 9999999, 5, 8, 8, 8]
n = len(arr)

# Function call
sortByFrequency(arr, n)

print(*arr)

# This code is contributed by phasing17
