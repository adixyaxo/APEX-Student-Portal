/* ============================================================
   APEX — Profile JS
   ============================================================ */

/* ── Grade mapping (10-point UGC scale) ── */
const GRADE_MAP = {
  10: 'O', 9: 'A+', 8: 'A', 7: 'B+', 6: 'B', 5: 'C', 4: 'P', 0: 'F'
};

const GRADE_CLASS = {
  'O': 'grade-o', 'A+': 'grade-ap', 'A': 'grade-a',
  'B+': 'grade-b', 'B': 'grade-b', 'C': 'grade-b', 'P': 'grade-b', 'F': 'grade-b'
};

function getGradePoint(total) {
  if (total >= 90) return 10;
  if (total >= 80) return 9;
  if (total >= 70) return 8;
  if (total >= 60) return 7;
  if (total >= 50) return 6;
  if (total >= 45) return 5;
  if (total >= 40) return 4;
  return 0;
}

function getGrade(total) {
  return GRADE_MAP[getGradePoint(total)];
}

/* ── In-memory subjects store ── */
let subjects = [
  { id: 1, name: 'Data Structures & Algorithms', code: 'CSE201', credits: 4, internal: 38, external: 62 },
  { id: 2, name: 'Operating Systems',             code: 'CSE204', credits: 4, internal: 35, external: 56 },
  { id: 3, name: 'Computer Networks',             code: 'CSE207', credits: 4, internal: 36, external: 52 },
  { id: 4, name: 'Basic Electrical Engineering',  code: 'ECL110', credits: 3, internal: 32, external: 49 },
  { id: 5, name: 'Mathematics III',               code: 'MTH201', credits: 4, internal: 34, external: 58 },
];

let nextId = 6;

/* ── Render ── */
function renderMarks() {
  const list  = document.getElementById('marksList');
  const empty = document.getElementById('marksEmpty');
  if (!list) return;

  if (subjects.length === 0) {
    list.innerHTML = '';
    if (empty) empty.style.display = '';
    updateSGPA();
    return;
  }
  if (empty) empty.style.display = 'none';

  list.innerHTML = subjects.map(s => {
    const total = s.internal + s.external;
    const grade = getGrade(total);
    const cls   = GRADE_CLASS[grade] || 'grade-b';
    return `
      <li class="marks-row" data-id="${s.id}">
        <span class="mk-subject">${escHtml(s.name)}</span>
        <span class="mk-code">${escHtml(s.code)}</span>
        <span class="mk-credits">${s.credits}</span>
        <span class="mk-internal">${s.internal}</span>
        <span class="mk-external">${s.external}</span>
        <span class="mk-total">${total}</span>
        <span class="mk-grade ${cls}">${grade}</span>
        <button class="row-del-btn" aria-label="Remove ${escHtml(s.name)}"
                onclick="removeSubject(${s.id})">×</button>
      </li>`;
  }).join('');

  updateSGPA();
}

/* ── SGPA calculation ── */
function updateSGPA() {
  const sgpaEl = document.getElementById('sgpaCalc');
  if (!sgpaEl) return;

  if (subjects.length === 0) { sgpaEl.textContent = '—'; return; }

  let sumGPxC = 0, sumC = 0;
  subjects.forEach(s => {
    const total = s.internal + s.external;
    const gp    = getGradePoint(total);
    sumGPxC += gp * s.credits;
    sumC    += s.credits;
  });

  const sgpa = sumC > 0 ? (sumGPxC / sumC).toFixed(2) : '—';
  sgpaEl.textContent = sgpa;
}

/* ── Remove subject ── */
window.removeSubject = function(id) {
  subjects = subjects.filter(s => s.id !== id);
  renderMarks();
  /*
    BACKEND HOOK:
    fetch(`/api/subjects/${id}`, { method: 'DELETE', headers: authHeaders() });
  */
};

/* ── Add subject panel ── */
const addBtn   = document.getElementById('addSubjectBtn');
const panel    = document.getElementById('addSubjectPanel');
const closeBtn = document.getElementById('closeAddPanel');
const cancelBtn = document.getElementById('cancelAddSubj');

function openPanel()  { if (panel) panel.style.display = ''; }
function closePanel() { if (panel) panel.style.display = 'none'; }

if (addBtn)   addBtn.addEventListener('click', openPanel);
if (closeBtn) closeBtn.addEventListener('click', closePanel);
if (cancelBtn) cancelBtn.addEventListener('click', closePanel);

const addForm = document.getElementById('addSubjectForm');
if (addForm) {
  addForm.addEventListener('submit', (e) => {
    e.preventDefault();

    const name     = document.getElementById('subjName').value.trim();
    const code     = document.getElementById('subjCode').value.trim();
    const credits  = parseInt(document.getElementById('subjCredits').value, 10);
    const internal = parseInt(document.getElementById('subjInternal').value, 10);
    const external = parseInt(document.getElementById('subjExternal').value, 10);

    if (!name || !code || isNaN(credits) || isNaN(internal) || isNaN(external)) return;
    if (internal < 0 || internal > 40) { alert('Internal marks must be 0–40.'); return; }
    if (external < 0 || external > 60) { alert('External marks must be 0–60.'); return; }

    subjects.push({ id: nextId++, name, code, credits, internal, external });
    renderMarks();
    addForm.reset();
    closePanel();

    /*
      BACKEND HOOK:
      fetch('/api/subjects', {
        method: 'POST',
        headers: { 'Content-Type': 'application/json', ...authHeaders() },
        body: JSON.stringify({ name, code, credits, internal, external })
      });
    */
  });
}

/* ── Edit personal info toggle ── */
const editInfoBtn   = document.getElementById('editInfoBtn');
const infoActions   = document.getElementById('infoActions');
const cancelInfoBtn = document.getElementById('cancelInfoBtn');
const infoInputs    = document.querySelectorAll('#infoForm .form-input');

if (editInfoBtn) {
  editInfoBtn.addEventListener('click', () => {
    const isEditing = editInfoBtn.classList.contains('active');
    if (!isEditing) {
      editInfoBtn.textContent = 'Editing…';
      editInfoBtn.classList.add('active');
      infoInputs.forEach(i => { i.disabled = false; });
      if (infoActions) infoActions.style.display = 'flex';
    }
  });
}

if (cancelInfoBtn) {
  cancelInfoBtn.addEventListener('click', () => {
    editInfoBtn.textContent = 'Edit';
    editInfoBtn.classList.remove('active');
    infoInputs.forEach(i => { i.disabled = true; });
    if (infoActions) infoActions.style.display = 'none';
  });
}

const infoForm = document.getElementById('infoForm');
if (infoForm) {
  infoForm.addEventListener('submit', (e) => {
    e.preventDefault();
    editInfoBtn.textContent = 'Edit';
    editInfoBtn.classList.remove('active');
    infoInputs.forEach(i => { i.disabled = true; });
    if (infoActions) infoActions.style.display = 'none';
    /*
      BACKEND HOOK:
      const payload = Object.fromEntries(
        [...infoInputs].map(i => [i.id, i.value])
      );
      fetch('/api/profile', {
        method: 'PATCH',
        headers: { 'Content-Type': 'application/json', ...authHeaders() },
        body: JSON.stringify(payload)
      });
    */
  });
}

/* ── Utility ── */
function escHtml(str) {
  return str.replace(/[&<>"']/g, c => ({
    '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;', "'": '&#39;'
  }[c]));
}

function authHeaders() {
  const token = localStorage.getItem('apex_token');
  return token ? { Authorization: `Bearer ${token}` } : {};
}

/* ── Init ── */
renderMarks();
