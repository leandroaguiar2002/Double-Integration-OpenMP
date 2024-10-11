#%%
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
# %%
df = pd.read_csv('results.csv')
df
# %%
df['Combined_Intervals'] = df.apply(lambda row: f"({row[' Intervals_x_axis']}, {row[' Intervals_y_axis']})", axis=1)
df
# %%
threads = df['Threads'].unique()
# %%
plt.figure(figsize=(10, 6))

for thread in threads:
    df_thread = df[df['Threads'] == thread]
    plt.plot(df_thread['Combined_Intervals'], df_thread[' Time Taken'], label=f'Threads: {thread}')

plt.xlabel('(Intervals_x_axis, Intervals_y_axis)')
plt.ylabel('Time Taken in seconds')
plt.title('Relação entre Intervals e Time Taken para diferentes Threads')

plt.legend()
plt.xticks(rotation=45)

plt.tight_layout()
plt.show()