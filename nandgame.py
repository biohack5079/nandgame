import tkinter

root = tkinter.Tk()
root.title("NANDGAME")
root.minsize(800, 450)
top = tkinter.Label(root, text="\nNANDGAME\n", font=("メイリオ", 16, "bold"))
top.pack()
top = tkinter.Label(root, text="1か0を入力してください", font=("メイリオ", 12, "bold"))
top.pack()

e1 = tkinter.Entry(root)
e1.pack()
e2 = tkinter.Entry(root)
e2.pack()
button = tkinter.Button(root, text="1か0を入力")
button.pack()


def nandgame():
    x = int(e1.get())
    y = int(e2.get())
    display = "AND=" + str(x*y) + "です\n""NAND=" + str(1-x*y) + "です\n""OR=" + str(x+y-x*y) + "です\n""NOR=" + str(1-x-y+x*y) + "です\n""XOR=" + str(x+y-2*x*y) + "です\n""XNOR=" + str(1-x-y+2*x*y) + "です\n"
    top["text"] = display



button["command"] = nandgame
root.mainloop()
