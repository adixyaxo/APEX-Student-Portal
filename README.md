# APEX — Academic Performance Exchange

A university-grade student ranking and CGPA platform built with a C++ backend and a hand-crafted HTML/CSS frontend. Designed for NorthCap University, Gurugram.

---

## Overview

APEX takes student academic data from a single authoritative source — the university records system — runs it through a deterministic C++ ranking engine, and surfaces the results through a clean authenticated web interface. Rankings update on each grade submission cycle.

The design philosophy is **hyper-minimal and cinematic**: black-and-white typography, no frameworks, no decoration for its own sake. Rank is visualised through opacity — the top student renders at full presence; each subsequent position fades fractionally, encoding hierarchy through visual weight alone.

---

## Pages

| File | Route | Purpose |
|------|-------|---------|
| `login.html` | `/login` | Authentication via enrollment ID and password |
| `index.html` | `/` | Top-10 rankings leaderboard with live search |
| `profile.html` | `/profile` | Personal dashboard — marks entry, SGPA, CGPA chart |
| `about.html` | `/about` | Project overview, architecture, CGPA methodology |

---

## Project structure

```
apex/
├── login.html
├── index.html
├── profile.html
├── about.html
│
├── css/
│   ├── style.css        # Global tokens, typography, nav, footer, shared components
│   ├── login.css        # Split-panel auth layout
│   ├── index.css        # Rankings table with opacity-fade signature
│   ├── profile.css      # Marks table, CGPA chart, edit forms
│   └── about.css        # Architecture diagram, grade scale, team block
│
└── js/
    ├── login.js         # Counter animation, form validation, auth fetch hook
    ├── index.js         # Live search filter on rankings list
    └── profile.js       # Subject CRUD, SGPA calculation, edit-info toggle
```

---

## Design system

### Palette

| Token | Hex | Usage |
|-------|-----|-------|
| `--white` | `#FFFFFF` | Page backgrounds |
| `--paper` | `#F7F7F7` | Hover states, inset panels |
| `--black` | `#000000` | Primary text, borders, filled buttons |
| `--near-black` | `#0D0D0D` | Avatars, active chart bars |
| `--grey-dark` | `#3A3A3A` | Body copy |
| `--grey-mid` | `#888888` | Labels, captions, metadata |
| `--grey-light` | `#D0D0D0` | Borders (light variant) |
| `--grey-faint` | `#EFEFEF` | Empty bars, backgrounds |

### Typography

| Role | Family | Notes |
|------|--------|-------|
| Display | EB Garamond | Headlines, italic accents, the logo word |
| Body | Inter | UI text, labels, buttons |
| Mono | JetBrains Mono | Enrollment IDs, CGPA values, scores, code |

### Signature element

The rankings list uses `--row-opacity` as a CSS custom property set inline on each row. Rank 1 renders at `opacity: 1.00`; each subsequent rank steps down by `~0.08`, ending at `opacity: 0.28` for Rank 10. A left-border accent bar scales its height proportionally with the same value. Hover overrides opacity back to `1` on any row.

---

## Stack

| Layer | Technology |
|-------|------------|
| Ranking engine | C++17 — weighted CGPA, O(n log n) sort |
| HTTP server | [cpp-httplib](https://github.com/yhirose/cpp-httplib) — single-header HTTP/HTTPS |
| Frontend | HTML5, CSS3, Vanilla JS — zero external dependencies |
| Auth | JWT tokens via C++ backend; `localStorage` on the client |

---

## CGPA methodology

Follows the UGC 10-point grading scale:

```
SGPA  = Σ (Grade Point × Credits)  /  Σ Credits
CGPA  = Σ (SGPA × Semester Credits) /  Σ Total Credits
```

| Marks | Grade | Points |
|-------|-------|--------|
| 90–100 | O | 10 |
| 80–89 | A+ | 9 |
| 70–79 | A | 8 |
| 60–69 | B+ | 7 |
| 50–59 | B | 6 |
| 45–49 | C | 5 |
| 40–44 | P | 4 |
| 0–39 | F | 0 |

---

## Connecting the backend

Each JS file contains clearly marked `BACKEND HOOK` comments. Replace the simulated logic at those points with real `fetch()` calls to the C++ server endpoints.

**Login** — `js/login.js`:
```javascript
const res = await fetch('/api/auth/login', {
  method: 'POST',
  headers: { 'Content-Type': 'application/json' },
  body: JSON.stringify({ enrollment, password })
});
const { token } = await res.json();
localStorage.setItem('apex_token', token);
```

**Rankings** — replace static HTML list with:
```javascript
const res = await fetch('/api/rankings?limit=10', {
  headers: { Authorization: `Bearer ${localStorage.getItem('apex_token')}` }
});
const { rankings } = await res.json();
// Render rows from rankings array
```

**Profile / subjects** — `js/profile.js`:
```javascript
// POST /api/subjects   — add subject
// DELETE /api/subjects/:id — remove subject
// PATCH /api/profile   — update personal info
```

---

## Running locally

No build step. Open any `.html` file directly in a browser for UI development.

For backend integration, start the cpp-httplib server and ensure the HTML files are served from the same origin to avoid CORS issues, or configure the C++ server with appropriate CORS headers.

```bash
# Build and run the C++ server (adjust to your build setup)
g++ -std=c++17 -o apex_server main.cpp -lpthread
./apex_server

# Frontend — serve static files
python3 -m http.server 8080
# then open http://localhost:8080
```

---

## Authors

Built at **NorthCap University, Gurugram** — B.Tech CSE group project.

| Name | Role | Enrollment |
|------|------|------------|
| Aditya Dagar | Routing · HTTP server · Project lead | 22SCSE101234 |

---

*APEX v2.1.0 · Jan–Jun 2025*
