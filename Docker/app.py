# app.py

from flask import Flask, jsonify, request
import sqlite3

app = Flask(__name__)

@app.route('/')
def index_page():
    return '<h1>Welcome to Flask Books App</h1>'

@app.route('/books', methods=['GET'])
def get_books():
    conn = sqlite3.connect('books.db')
    cur = conn.cursor()
    cur.execute('SELECT * FROM books')
    rows = cur.fetchall()
    books = []
    for row in rows:
        book = {
            'id': row[0],
            'title': row[1],
            'author': row[2],
            'published': row[3]
        }
        books.append(book)
    conn.close()
    return jsonify(books)

@app.route('/books/<int:book_id>', methods=['GET'])
def get_book(book_id):
    conn = sqlite3.connect('books.db')
    cur = conn.cursor()
    cur.execute('SELECT * FROM books WHERE id=?', (book_id,))
    row = cur.fetchone()
    if row:
        book = {
            'id': row[0],
            'title': row[1],
            'author': row[2],
            'published': row[3]
        }
        conn.close()
        return jsonify(book)
    else:
        conn.close()
        return jsonify({'error': 'Book not found'})

@app.route('/books', methods=['POST'])
def create_book():
    book = request.get_json()
    conn = sqlite3.connect('books.db')
    cur = conn.cursor()
    cur.execute('INSERT INTO books (title, author, published) VALUES (?, ?, ?)', (book['title'], book['author'], book['published']))
    book_id = cur.lastrowid
    conn.commit()
    conn.close()
    return jsonify({'id': book_id, 'message': 'Book created successfully'})

@app.route('/books/<int:book_id>', methods=['PUT'])
def update_book(book_id):
    book = request.get_json()
    conn = sqlite3.connect('books.db')
    cur = conn.cursor()
    cur.execute('UPDATE books SET title=?, author=?, published=? WHERE id=?', (book['title'], book['author'], book['published'], book_id))
    conn.commit()
    conn.close()
    return jsonify({'message': 'Book updated successfully'})

@app.route('/books/<int:book_id>', methods=['DELETE'])
def delete_book(book_id):
    conn = sqlite3.connect('books.db')
    cur = conn.cursor()
    cur.execute('DELETE FROM books WHERE id=?', (book_id,))
    conn.commit()
    conn.close()
    return jsonify({'message': 'Book deleted successfully'})


if __name__ == '__main__':
    app.run()
