import numpy as np
import pandas as pd
from sklearn.feature_selection import SelectKBest
from sklearn.feature_selection import f_classif
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import LabelEncoder
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from micromlgen import port

def choices_to_colors(actions):
    color_mapping = {
        0: 'blue', # Left 
        1: 'cyan', # Right
        2: 'magenta', # Forward
        3: 'red', # Mysterious 3
    }
    
    return [color_mapping.get(action, 'black') for action in actions]

# Load the csv data into a pandas dataframe
data = pd.read_csv(r"csv_outputs\2024_03_31_0903\generation_0\car_15_data.csv", header=None, delimiter=" ")

# Rename the last column to 'Label'
data.rename(columns={data.columns[-1]: 'Label'}, inplace=True)

# Printing dataframe for validation
print(data)
data.reset_index(drop=True, inplace=True)

x = data.iloc[:, :-1]
y = data.iloc[:, -1]

print("unique: " + str(pd.unique(y)))
#get index of first row where value in 'team' column is equal to 'B'
print("3 index: " + str(data[data.Label == 3].index[0]))
#input()

label_encoder = LabelEncoder()
y = label_encoder.fit_transform(y)

print("y")
print(y)
print("y length = " + str(len(y)))
#input()

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=42)

k = 5
k_best = SelectKBest(score_func=f_classif, k=k)
k_best.fit(x_train, y_train)

selected_feature_indices = k_best.get_support(indices=True)
print("selected_feature_indices: ", selected_feature_indices)

plt.scatter(data.iloc[:, selected_feature_indices[0]], data.iloc[:, selected_feature_indices[4]], c = choices_to_colors(data.iloc[:, -1]), s=8)
#plt.show()

clf = RandomForestClassifier(max_depth=3, random_state=42)
clf.fit(x_train.iloc[:, selected_feature_indices], y_train)

y_pred = clf.predict(x_test.iloc[:, selected_feature_indices])

accuracy = accuracy_score(y_test, y_pred)
print(f'Accuracy: {accuracy}')

class_names = label_encoder.classes_
print("Classes: " + str(label_encoder.classes_))
#input()
target_names=list(map(str, class_names))
report = classification_report(y_test, y_pred, target_names=target_names, zero_division=0, labels=[0, 1, 2, 3])
print('Classification Report:\n', report)
