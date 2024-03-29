import random
import string


def generate_word():
    return "".join(random.choices(string.ascii_uppercase, k=random.randint(3, 10)))


def generate_clue():
    relation = "".join(random.choices(string.ascii_lowercase, k=random.randint(3, 8)))
    relation_value = "".join(
        random.choices(string.ascii_lowercase, k=random.randint(5, 15))
    )
    return f"{relation}: {relation_value}"


def generate_entry():
    num_clues = random.randint(1, 5)  # Generate random number of clues per word
    word = generate_word()
    clues = [generate_clue() for _ in range(num_clues)]
    return (
        f"Object: {word}\n" + "\n".join(clues) + "\n\n"
    )  # Add an empty line between entries


with open("word_entries.txt", "w") as f:
    for _ in range(150):  # Generate 150 word entries
        entry = generate_entry()
        f.write(entry)
