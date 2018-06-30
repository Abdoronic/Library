int merge(int arr[], int temp[], int left, int mid, int right) {
	int i = left, j = mid + 1, k = left, inv = 0;
	while(i <= mid && j <= right) {
		if(arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		} else {
			temp[k++] = arr[j++];
			inv += mid - i + 1;
		}
	}
	while(i <= mid)
		temp[k++] = arr[i++];
	while(j <= right)
		temp[k++] = arr[j++];
	for(i = left; i <= right; i++)
		arr[i] = temp[i];
	return inv;
}

int sort(int arr[], int temp[], int left, int right) {
	if(left < right) {
		int mid = (right - left)/2 + left;
		int inv = sort(arr, temp, left, mid);
		inv += sort(arr, temp, mid + 1, right);
		inv += merge(arr, temp, left, mid, right);
		return inv;
	}
	return 0;
}

int mergeSort(int arr[], int N) {
	int temp[N];
	return sort(arr, temp, 0, N-1);
}
