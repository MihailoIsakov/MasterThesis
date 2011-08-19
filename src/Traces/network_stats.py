import os, json, math

def sample_deviation(sample_list):
  mean = average_list(sample_list)

  accum = 0
  for val in sample_list:
    diff = val - mean
    accum += diff * diff
  
  return math.sqrt(accum / len(sample_list))


def average_list(avg_list):
  return sum(avg_list) * 1.0 / len(avg_list) * 1.0

def average_suite(data_list, min_list, max_list):
  average     = average_list(data_list)
  min_average = average_list(min_list)
  max_average = average_list(max_list)
  std_value   = sample_deviation(data_list)
  return (average, min_average, max_average, std_value)

paths = ["GREEDY", "GPSR", "GOAFR"]
sizes = [100, 250]

for path in paths:
  for i in xrange(10):
    nodes = 10 * (i + 1)
    for size in sizes:
      hops = []
      time = []
      recv = 0
      sends = 0
      
      min_hops = []
      max_hops = []

      min_time = []
      max_time = []

      for j in xrange(2):
        filename = "%s_json/%s-%s-%s-%s.json" % (path, path, nodes, size, j)
        f = open(filename, 'r')
	json_data = f.read()
	f.close()
	data = json.loads(json_data)

	# Get insert the data	
        local_hops = data[0]
	local_time = data[1]
        local_percent = data[2]
        
        hops.extend(local_hops)
	time.extend(local_time)
	
        min_time.append(min(local_time))
        max_time.append(max(local_time))
        
	min_hops.append(min(local_hops))
	max_hops.append(max(local_hops))

        recv  += local_percent[0]
        sends += local_percent[1]
      
      # Find the values:
      percent = (recv * 1.0 / sends * 1.0) * 100
      
      hop_data  = average_suite(hops, min_hops, max_hops)
      time_data = average_suite(time, min_time, max_time)

      data = (percent, hop_data, time_data)

      save_data = json.dumps(data)
      filename = "%s_results/%s-%s-%s.json" % (path, path, nodes, size)
      f = open(filename, "w")
      f.write(save_data)
      f.close()

