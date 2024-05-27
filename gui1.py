import tkinter as tk
from tkinter import messagebox, filedialog
import subprocess
import os

def run_assembler():
    input_text = input_text_widget.get("1.0", tk.END)
    
    # Write input to sicxe.txt
    with open('sicxe.txt', 'w') as file:
        file.write(input_text)
    
    # Run Sic_Assembler.exe
    symtab_text.delete('1.0', tk.END)  # Clear the symtab text area
    objtab_text.delete('1.0', tk.END)  # Clear the objtab text area
    outHTE_text.delete('1.0', tk.END)  # Clear the outHTE text area
    status_label.config(text="Running Sic_Assembler.exe...")
    root.update_idletasks()  # Refresh the UI

    run_process = subprocess.run(['./Sic_Assembler.exe'])
    if run_process.returncode != 0:
        messagebox.showerror("Error", "Failed to run Sic_Assembler.exe")
        status_label.config(text="Execution failed.")
        return
    
    status_label.config(text="Displaying output files...")
    # Display content of symtab.txt
    display_file_content('symtab.txt', symtab_text)
    # Display content of objtab.txt
    display_file_content('objtab.txt', objtab_text)
    # Display content of outHTE.txt
    display_file_content('outHTE.txt', outHTE_text)
    status_label.config(text="Done.")

def display_file_content(file_path, text_widget):
    if os.path.exists(file_path):
        with open(file_path, 'r') as file:
            content = file.read()
            text_widget.insert(tk.END, content)
    else:
        messagebox.showerror("Error", f"File {file_path} not found")

def open_file():
    file_path = filedialog.askopenfilename()
    if file_path:
        with open(file_path, 'r') as file:
            input_text_widget.delete("1.0", tk.END)
            input_text_widget.insert(tk.END, file.read())

# Create main window
root = tk.Tk()
root.title("SIC/XE Assembler Interface")

# Create input frame
input_frame = tk.Frame(root)
input_frame.pack(pady=10, fill=tk.BOTH, expand=True)

tk.Label(input_frame, text="Enter Input:").pack(anchor='w')
input_text_widget = tk.Text(input_frame, wrap=tk.WORD, width=80, height=10)
input_text_widget.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

open_button = tk.Button(input_frame, text="Open", command=open_file)
open_button.pack(side=tk.LEFT, padx=5)

submit_button = tk.Button(input_frame, text="Submit", command=run_assembler)
submit_button.pack(side=tk.LEFT, padx=5)

status_label = tk.Label(root, text="", fg="blue")
status_label.pack(pady=5)

# Create output frames
output_frame = tk.Frame(root)
output_frame.pack(pady=10, fill=tk.BOTH, expand=True)

tk.Label(output_frame, text="SYM Table Output:").grid(row=0, column=0, padx=10, pady=5)
symtab_text = tk.Text(output_frame, wrap=tk.WORD, width=50, height=10)
symtab_text.grid(row=1, column=0, padx=10, pady=5)

tk.Label(output_frame, text="OBJ Table Output:").grid(row=0, column=1, padx=10, pady=5)
objtab_text = tk.Text(output_frame, wrap=tk.WORD, width=50, height=10)
objtab_text.grid(row=1, column=1, padx=10, pady=5)

tk.Label(output_frame, text="HTE Output:").grid(row=0, column=2, padx=10, pady=5)
outHTE_text = tk.Text(output_frame, wrap=tk.WORD, width=50, height=10)
outHTE_text.grid(row=1, column=2, padx=10, pady=5)

# Start the Tkinter event loop
root.mainloop()
