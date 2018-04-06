import json
import os
import pickle


project_paths = {
	'dataset': ['resources', 'datasets'],
	'model': ['models'],
	'profile_t': ['profiles', 'training'],
	'profile_p': ['profiles', 'predicting'],
	'stopwords': ['resources', 'stopwords'],
}




def append_text(file_name, min_length = 0):

	""" Coroutine that appends the received text at the end of a file
	Arguments:
	----------
		file_name:
			type: string
			info: appendable file name
		min_length:
			type: int (optional)
			info: minimum length to append a text to the file
	Yield:
	----------
		text:
			type: string
			info: text to append in the file
	"""

	file_path = compute_path(file_name, 'dataset')

	file_dir = file_path.replace(file_name, '')
	os.makedirs(file_dir, exist_ok = True)

	try:
		file = open(file_path, 'a', encoding = 'utf-8')

		try:
			while True:
				text = yield
				if len(text) >= min_length: file.write(text + '\n')

		finally:
			file.close()

	except IOError:
		exit('The file ' + file_path + ' cannot be opened')




def compute_path(file_name, file_type):

	""" Reads the lines of a file and returns them inside a list
	Arguments:
	----------
		file_name:
			type: string
			info: desired file name
		file_type:
			type: string
			info: used to determine the proper path
	Returns:
	----------
		lines:
			type: string
			info: absolute path to the desired file
	"""

	try:
		project_root = str(os.path.dirname(os.getcwd()))

		path = [project_root]
		path = path + project_paths[file_type]
		path = path + [file_name]

		return os.path.join(*path)

	except KeyError:
		exit('The file type "' + file_type + '" is not defined')




def load_object(file_name, file_type):

	""" Loads an object from the specified file
	Arguments:
		----------
		file_name:
			type: string
			info: saved object file name
		file_type:
			type: string
			info: used to determine the proper path
	Returns:
	----------
		obj:
			type: dict
			info: dictionary containing the object information
	"""

	file_path = compute_path(file_name, file_type)

	try:
		file = open(file_path, 'rb')
		obj = pickle.load(file)
		file.close()

		return obj

	except IOError:
		exit('The object could not be loaded from ' + file_path)




def save_object(obj, file_name, file_type):

	""" Saves an object in the specified path
	Arguments:
	----------
		obj:
			type: object
			info: instance of a class that will be serialized
		file_name:
			type: string
			info: saved object file name
		file_type:
			type: string
			info: used to determine the proper path
	"""

	file_path = compute_path(file_name, file_type)

	file_dir = file_path.replace(file_name, '')
	os.makedirs(file_dir, exist_ok = True)

	try:
		file = open(file_path, 'wb')
		pickle.dump(obj.__dict__, file)
		file.close()

	except IOError:
		exit('The object could not be saved in ' + file_path)




def read_json(file_name, file_type):

	""" Reads the lines of a file and returns them inside a list
	Arguments:
	----------
		file_name:
			type: string
			info: readable file name
		file_type:
			type: string
			info: used to determine the proper path
	Returns:
	----------
		json_dict:
			type: dict
			info: dictionary containing the parsed JSON file
	"""

	file_path = compute_path(file_name, file_type)

	try:
		file = open(file_path, 'r', encoding = 'utf-8')
		json_dict = json.load(file)
		file.close()

		return json_dict

	except IOError:
		exit('The file ' + file_name + ' cannot be opened')




def read_lines(file_name, file_type):

	""" Reads the lines of a file and returns them inside a list
	Arguments:
	----------
		file_name:
			type: string
			info: readable file name
		file_type:
			type: string
			info: used to determine the proper path
	Returns:
	----------
		lines:
			type: list
			info: file lines (separated by the new line character)
	"""

	file_path = compute_path(file_name, file_type)

	try:
		file = open(file_path, 'r', encoding = 'utf-8')
		lines = file.read().splitlines()
		file.close()

		return lines

	except IOError:
		exit('The file ' + file_name + ' cannot be opened')
