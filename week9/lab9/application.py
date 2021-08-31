import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        if request.form['submit_button'] == "Add":
            if request.form.get("name") != "" and request.form.get("month") != "" and request.form.get("day") != "":
                name = str(request.form.get("name"))
                month = int(request.form.get("month"))
                day = int(request.form.get("day"))
                nameDB = db.execute("SELECT name FROM birthdays WHERE name=?",name)
                print(nameDB)
                if not nameDB:
                    db.execute("INSERT INTO birthdays (name,month,day) VALUES (?,?,?)",name,month,day)
                else:
                    db.execute("UPDATE birthdays SET month=?, day=? WHERE name=?",month,day,name)
        elif request.form['submit_button'] == "Delete":
            if request.form.get("deletename") != "":
                name = str(request.form.get("deletename"))
                db.execute("DELETE FROM birthdays WHERE name=?",name)
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        persons = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", persons=persons)


