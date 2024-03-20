import asyncio
import speech_recognition as sr
from characterai import PyAsyncCAI
from gtts import gTTS
import subprocess
from PIL import Image, ImageTk
import tkinter as tk
import os



# Prototype Function to display animated GIF
# #def display_gif(root):
#     gif_path = r"imageMove.gif"  # Replace with the path to your animated GIF
#     gif = Image.open(gif_path)
    
#     # Create a label to display the animated GIF
#     gif_label = tk.Label(root)
#     gif_label.pack()

#     # Function to update the animated GIF
#     def update_gif():
#         frame = gif.tell()
    #     gif_label.configure(image=ImageTk.PhotoImage(gif))
    #     gif_label.image = ImageTk.PhotoImage(gif)
    #     gif.seek(frame + 1)
    #     root.after(100, update_gif)  # Adjust the delay (milliseconds) for animation speed
        
    # # Start the GIF animation
    # update_gif()
# Function to display image
def display_image(root):
    img_path = r"imageMove.gif"  # Replace with the path to your image
    img = Image.open(img_path)
    img = img.resize((300, 300))  # Adjust size as needed

    # Convert the image for Tkinter
    img_tk = ImageTk.PhotoImage(img)

    # Create a label to display the image
    img_label = tk.Label(root, image=img_tk)
    img_label.image = img_tk  # Keep a reference to avoid garbage collection
    img_label.pack()

    # Function to lift the image label to the top layer
    def lift_to_top():
        img_label.lift()
        # Schedule the lift_to_top function to be called again after 100 milliseconds
        root.after(100, lift_to_top)

    # Start the continuous lifting
    lift_to_top()

async def execute_python_file(file_name):
    try:
        subprocess.run(['python', file_name])  # Replace 'python' with 'python3' if needed
    except FileNotFoundError:
        print(f"File '{file_name}' not found or unable to execute.")
def terminate_vlc():
    try:
        # Terminate VLC process using taskkill command
        subprocess.run(["taskkill", "/f", "/im", "vlc.exe"], check=True)
        print("VLC process terminated successfully.")
    except subprocess.CalledProcessError as e:
        print(f"Error occurred while terminating VLC process: {e}")

async def main():
    root = tk.Tk()
    root.title("Study Chat")

    # Display image on top
    # display_gif(root) prototype
    display_image(root)
    #YntB_ZeqRq2l_aVf2gWDCZl4oBttQzDvhj9cXafWcF8 68c4a39fbf35acc12d561282dddf3151dc01cc7b hu tao kZ3_qgkyiYvcRqgwv1WE2WQeME9CZy1yrCnMx98wyfk
    client = PyAsyncCAI('68c4a39fbf35acc12d561282dddf3151dc01cc7b') 
    char = 'U3dJdreV9rrvUiAnILMauI-oNH838a8E_kEYfOFPalE'  


    #U3dJdreV9rrvUiAnILMauI-oNH838a8E_kEYfOFPalE
    #68c4a39fbf35acc12d561282dddf3151dc01cc7b
    chat = await client.chat.get_chat(char)
    participants = chat['participants']

    if not participants[0]['is_human']:
        tgt = participants[0]['user']['username']
    else:
        tgt = participants[1]['user']['username']

    is_conversation_mode = False

    while True:
        if is_conversation_mode:
            recognizer = sr.Recognizer()
            with sr.Microphone() as source:
                print("Say something:")
                audio = recognizer.listen(source)

            try:
                message = recognizer.recognize_google(audio, language='en')
                print('You said:', message)
                # Rest of the speech-to-text and chat interaction code...
                # Special keyword for toggling modes
                if message.lower() == 'toggle':
                    is_conversation_mode = not is_conversation_mode
                    print("Mode toggled.")
                    continue  # Skip the rest of the loop

                # Send the text message to the chat
                data = await client.chat.send_message(chat['external_id'], tgt, message)

                name = data['src_char']['participant']['name']
                text = data['replies'][0]['text']

                print(f"{name}: {text}")

                # Text-to-Speech using gTTS with speed and pitch adjustments
                tts = gTTS(text, lang='zh-CN', slow=False)
                tts.save(r'temp.mp3')

                # Play the audio using vlc without GUI (provide full path to vlc.exe)
                vlc_path = r'vlc.exe'
                subprocess.Popen([vlc_path, '--intf', 'dummy', r'temp.mp3'], shell=True)

            except sr.UnknownValueError:
                print("Sorry, could not understand audio.")
            except sr.RequestError as e:
                print(f"Could not request results from Google Web Speech API; {e}")
        else:
            message = input('You: ')

            if message.lower() == 'exit':
                terminate_vlc()
                os.remove("temp.mp3")
                break

            # Special keyword for toggling modes
            if message.lower() == 'toggle':
                is_conversation_mode = not is_conversation_mode
                print("Mode toggled.")
                continue  # Skip the rest of the loop

            data = await client.chat.send_message(chat['external_id'], tgt, message)

            name = data['src_char']['participant']['name']
            text = data['replies'][0]['text']

            print(f"{name}: {text}")

            # Text-to-Speech using gTTS with speed and pitch adjustments
            tts = gTTS(text, lang='zh-CN', slow=False)
            tts.save(r'temp.mp3')

            # Play the audio using vlc without GUI (provide full path to vlc.exe)
            vlc_path = r'vlc.exe'
            speed = 1.2
            subprocess.Popen([vlc_path, '--intf', 'dummy', '--rate', str(speed), r'temp.mp3'], shell=True)

if __name__ == "__main__":
    asyncio.run(main())
