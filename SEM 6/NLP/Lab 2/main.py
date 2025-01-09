import nltk
from nltk.corpus import gutenberg, reuters, webtext, genesis, brown
from nltk.tokenize import word_tokenize, sent_tokenize
from nltk.corpus import stopwords
from nltk.stem import PorterStemmer
import string
from collections import Counter

# Download required NLTK data
nltk.download('gutenberg')
nltk.download('reuters')
nltk.download('webtext')
nltk.download('genesis')
nltk.download('brown')
nltk.download('punkt')
nltk.download('averaged_perceptron_tagger')
nltk.download('stopwords')
nltk.download('universal_tagset')  # Added this line
nltk.download('averaged_perceptron_tagger_eng')

def print_corpus_stats():
    # Same as before...
    pass

def process_text(text):
    # Word tokenization
    words = word_tokenize(text)
    print(f"\nNumber of words: {len(words)}")
    
    # Sentence tokenization
    sentences = sent_tokenize(text)
    print(f"Number of sentences: {len(sentences)}")
    
    # File size before removing stop words
    original_size = len(words)
    print(f"File size (in words) before removing stop words: {original_size}")
    
    # Remove stopwords and punctuation
    stop_words = set(stopwords.words('english'))
    words_no_stop = [word.lower() for word in words 
                     if word.lower() not in stop_words 
                     and word not in string.punctuation]
    
    # File size after removing stop words
    processed_size = len(words_no_stop)
    print(f"File size (in words) after removing stop words: {processed_size}")
    
    # Count unique words
    unique_words = set(words_no_stop)
    print(f"Number of unique words: {len(unique_words)}")
    
    try:
        # POS Tagging with error handling
        pos_tags = nltk.pos_tag(words[:20])  # Only tagging first 20 words for demonstration
        print("\nPOS Tagging (first 20 words):")
        for word, tag in pos_tags:
            print(f"{word}: {tag}")
    except LookupError as e:
        print("\nError in POS tagging:", str(e))
        print("Some NLTK resources might be missing. Please ensure all required packages are downloaded.")
    
    # Stemming
    stemmer = PorterStemmer()
    stemmed_words = [stemmer.stem(word) for word in words_no_stop[:10]]  # Only stemming first 10 words
    print("\nStemming (first 10 words):")
    for original, stemmed in zip(words_no_stop[:10], stemmed_words):
        print(f"{original} -> {stemmed}")

def main():
    print("\nCorpus Statistics:")
    print_corpus_stats()
    
    print("\nProcessing sample text from Gutenberg corpus:")
    try:
        sample_text = gutenberg.raw('shakespeare-hamlet.txt')
        process_text(sample_text)
    except Exception as e:
        print(f"Error processing text: {str(e)}")

if __name__ == "__main__":
    main()