/* ============================================================
   APEX — Login JS
   ============================================================ */

/* ── Animated counters ── */
function animateCounter(el, target, duration = 1200) {
  const start = performance.now();
  const update = (now) => {
    const progress = Math.min((now - start) / duration, 1);
    const eased = 1 - Math.pow(1 - progress, 3); // ease-out cubic
    el.textContent = Math.round(eased * target);
    if (progress < 1) requestAnimationFrame(update);
  };
  requestAnimationFrame(update);
}

document.querySelectorAll('.stat-number[data-target]').forEach(el => {
  animateCounter(el, parseInt(el.dataset.target, 10));
});

/* ── Password toggle ── */
const togglePw = document.getElementById('togglePw');
const pwInput  = document.getElementById('password');

if (togglePw && pwInput) {
  togglePw.addEventListener('click', () => {
    const isHidden = pwInput.type === 'password';
    pwInput.type = isHidden ? 'text' : 'password';
  });
}

/* ── Form submission ── */
const form      = document.getElementById('loginForm');
const errorDiv  = document.getElementById('formError');
const submitBtn = form ? form.querySelector('.login-submit') : null;

function showError(msg) {
  if (!errorDiv) return;
  errorDiv.textContent = msg;
  errorDiv.classList.add('visible');
}

function clearError() {
  if (!errorDiv) return;
  errorDiv.textContent = '';
  errorDiv.classList.remove('visible');
}

function setLoading(on) {
  if (!submitBtn) return;
  submitBtn.classList.toggle('loading', on);
  submitBtn.disabled = on;
}

if (form) {
  form.addEventListener('submit', async (e) => {
    e.preventDefault();
    clearError();

    const enrollment = document.getElementById('enrollment').value.trim();
    const password   = document.getElementById('password').value;

    if (!enrollment) { showError('Enrollment ID is required.'); return; }
    if (!password)   { showError('Password is required.'); return; }

    setLoading(true);

    try {
      /*
        BACKEND HOOK:
        Replace the simulated delay below with a real fetch call:

        const res = await fetch('/api/auth/login', {
          method: 'POST',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ enrollment, password })
        });

        if (!res.ok) {
          const data = await res.json();
          throw new Error(data.message || 'Authentication failed.');
        }

        const { token } = await res.json();
        localStorage.setItem('apex_token', token);
      */

      // Simulated auth delay — remove when backend is connected
      await new Promise(r => setTimeout(r, 800));

      // Demo: any credentials pass
      window.location.href = '/';

    } catch (err) {
      setLoading(false);
      showError(err.message || 'Authentication failed. Please try again.');
    }
  });
}
