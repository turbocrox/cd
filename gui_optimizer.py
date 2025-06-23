import tkinter as tk
from tkinter import scrolledtext, messagebox
import subprocess
import os

class OptimizerGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("C++ Code Optimizer GUI")
        self.root.geometry("1350x600")

        # Main horizontal frame with grid for even sizing
        main_frame = tk.Frame(root)
        main_frame.pack(fill='both', expand=True)
        main_frame.columnconfigure(0, weight=1, minsize=350)
        main_frame.columnconfigure(1, weight=1, minsize=350)
        main_frame.columnconfigure(2, weight=1, minsize=350)

        # Input code section (left)
        input_frame = tk.Frame(main_frame)
        input_frame.grid(row=0, column=0, sticky='nsew', padx=(10,5), pady=10)
        tk.Label(input_frame, text="Input Code:", font=("Arial", 12, "bold")).pack(anchor='w')
        self.input_text = scrolledtext.ScrolledText(input_frame, height=30, font=("Consolas", 11))
        self.input_text.pack(fill='both', expand=True, pady=5)

        # TAC code section (middle)
        tac_frame = tk.Frame(main_frame)
        tac_frame.grid(row=0, column=1, sticky='nsew', padx=5, pady=10)
        tk.Label(tac_frame, text="TAC Code:", font=("Arial", 12, "bold")).pack(anchor='w')
        self.tac_text = scrolledtext.ScrolledText(tac_frame, height=30, font=("Consolas", 11), bg="#f0f0f0")
        self.tac_text.pack(fill='both', expand=True, pady=5)

        # Optimized code section (right)
        opt_frame = tk.Frame(main_frame)
        opt_frame.grid(row=0, column=2, sticky='nsew', padx=(5,10), pady=10)
        tk.Label(opt_frame, text="Optimized Code:", font=("Arial", 12, "bold")).pack(anchor='w')
        self.optimized_text = scrolledtext.ScrolledText(opt_frame, height=30, font=("Consolas", 11), bg="#e8ffe8")
        self.optimized_text.pack(fill='both', expand=True, pady=5)

        # Optimize button at the bottom, smaller size
        bottom_btn_frame = tk.Frame(root)
        bottom_btn_frame.pack(fill='x', pady=(0, 10))
        tk.Button(bottom_btn_frame, text="Optimize!", font=("Arial", 12, "bold"), bg="#4CAF50", fg="white", command=self.run_optimizer, height=1, width=12).pack(pady=2)

    def run_optimizer(self):
        code = self.input_text.get("1.0", tk.END).strip()
        if not code:
            messagebox.showwarning("No Input", "Please enter some code to optimize.")
            return
        # Write input to file
        with open("input_code.txt", "w", encoding="utf-8") as f:
            f.write(code)
        # Run the C++ optimizer
        exe = "compiler.exe" if os.name == "nt" else "./compiler"
        try:
            result = subprocess.run([exe, "input_code.txt"], capture_output=True, text=True, timeout=10)
            if result.returncode != 0:
                messagebox.showerror("Error", f"Optimizer failed:\n{result.stderr}")
                return
        except Exception as e:
            messagebox.showerror("Error", f"Failed to run optimizer: {e}")
            return
        # Read and display TAC
        try:
            with open("tac.txt", "r", encoding="utf-8") as f:
                tac = f.read()
        except:
            tac = "[Could not read tac.txt]"
        self.tac_text.delete("1.0", tk.END)
        self.tac_text.insert(tk.END, tac)
        # Read and display optimized code
        try:
            with open("optimized_output.txt", "r", encoding="utf-8") as f:
                opt = f.read()
        except:
            opt = "[Could not read optimized_output.txt]"
        self.optimized_text.delete("1.0", tk.END)
        self.optimized_text.insert(tk.END, opt)

if __name__ == "__main__":
    root = tk.Tk()
    app = OptimizerGUI(root)
    root.mainloop() 